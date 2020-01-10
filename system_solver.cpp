//
// Created by tomanm10 on 13.12.2019.
//

#include "system_solver.hpp"
#include "command.hpp"
#include <algorithm>
#include <stack>
#include <chrono>
#include <future>

std::pair<Matrix, Matrix> SystemSolver::decompose_lu(const Matrix &matrix) {
    int n = matrix.height;
    // upper triangular matrix
    Matrix matrix_U = matrix;
    // lower triangular matrix (square)
    Matrix matrix_L = MatrixCreator::get_identity(n);
    // permutation matrix (square)
    Matrix matrix_P = MatrixCreator::get_identity(n);
    int pivot_row_index = 0;

    for (int i = 0; i < matrix.width; ++i) {
        if (pivot_row_index < n) {
            int current_pivot = pivot_row_index;

            if (matrix_U.get_field(i, pivot_row_index) == 0) {

                for (int k = pivot_row_index + 1; k < n && current_pivot == pivot_row_index; ++k) {
                    if (matrix_U.get_field(i, k) != 0) {
                        current_pivot = k;
                    }
                }

                if (current_pivot != pivot_row_index) {
                    Matrix S = MatrixCreator::get_identity(n);

                    S.foreach_field([&pivot_row_index, &current_pivot, &S](int x, int y, double e) {
                        return (y == pivot_row_index) ?
                               S.get_field(x, current_pivot) :
                               ((y == current_pivot) ? S.get_field(x, pivot_row_index) : e);
                    });

                    matrix_U = S * matrix_U;
                    matrix_L = S * (matrix_L - MatrixCreator::get_identity(n)) + MatrixCreator::get_identity(n);
                    matrix_P = matrix_P * S;
                }
            } else {
                Matrix L = MatrixCreator::get_identity(n);

                L.foreach_field([&pivot_row_index, &matrix_U, &i](int x, int y, double e) {
                    return (x == pivot_row_index && y >= pivot_row_index + 1) ?
                           -(matrix_U.get_field(i, y) / matrix_U.get_field(i, pivot_row_index)) : e;
                });

                matrix_U = L * matrix_U;
                matrix_L = matrix_L * L;
                pivot_row_index++;
            }
        }
    }

    matrix_L.foreach_field([](int x, int y, double e) {
        return (x == y) ? e : -e;
    });

    return std::make_pair(matrix_L, matrix_U);
}

void SystemSolver::solve(std::ostream &ostream, const Matrix &matrix) {
    // capture time on start
    auto start = std::chrono::high_resolution_clock::now();

    ostream << "Solving matrix:" << std::endl << matrix;

    Matrix matrix_U = decompose_lu(matrix).second;
    matrix_U.augmented = true;

    ostream << "Upper triangular matrix:" << std::endl << matrix_U;

    // find pivot indexes
    std::pair<std::vector<double>, std::vector<double>> pivot_indexes = get_pivot_indexes(matrix_U);
    std::vector<double> pivots_column_indexes = pivot_indexes.first;
    std::vector<double> pivots_row_indexes = pivot_indexes.second;

    ostream << "Pivots are on columns:" << std::endl << pivots_column_indexes;
    ostream << "Pivots are on rows:" << std::endl << pivots_row_indexes;

    bool solution_exists =
            std::find(pivots_column_indexes.begin(), pivots_column_indexes.end(), matrix_U.width - 1) ==
            pivots_column_indexes.end();

    if (!solution_exists) {
        ostream << "Given linear system has no solution." << std::endl;
    } else {
        ostream << "Solution of the linear system:" << std::endl;

        std::vector<double> vector_p;
        std::vector<std::vector<double>> kernel;
        int rank = pivots_column_indexes.size();
        int defect = matrix_U.width - 1 - rank;
        std::vector<double> vector_b = matrix_U.get_column(matrix_U.width - 1);

        if (!CommandInterpreter::USING_MULTIPLE_THREADS) {
            // find particular solution
            vector_p = backward_substitution(matrix_U, vector_b, pivots_column_indexes, pivots_row_indexes);

            // find kernel if needed (defect > 0)
            for (int j = 0; j < defect; ++j) {
                std::vector<double> kernel_basis_vector =
                        backward_substitution(matrix_U, std::vector<double>(matrix_U.height, 0.0),
                                              pivots_column_indexes, pivots_row_indexes, j);
                kernel.push_back(kernel_basis_vector);
            }
        } else {
            // find particular solution
            auto vector_p_fut =
                    std::async(std::launch::async, &backward_substitution, matrix_U, vector_b,
                               pivots_column_indexes, pivots_row_indexes, -1);

            // find kernel if needed (defect > 0)
            std::vector<std::future<std::vector<double>>> kernel_fut;
            kernel_fut.reserve(defect);
            for (int j = 0; j < defect; ++j) {
                kernel_fut.emplace_back(
                        std::async(std::launch::async, &backward_substitution, matrix_U,
                                   std::vector<double>(matrix_U.height, 0.0),
                                   pivots_column_indexes, pivots_row_indexes, j));
            }

            // get all results from futures
            vector_p = vector_p_fut.get();
            for (std::future<std::vector<double>> &k : kernel_fut) {
                kernel.push_back(k.get());
            }
        }

        // print the solution
        if (!kernel.empty()) {
            ostream << "Particular solution is:" << std::endl;
            ostream << vector_p;
            ostream << "Basis of the kernel is:" << std::endl;
            for (const auto &i : kernel) {
                ostream << i;
            }
        } else {
            ostream << "Unique solution is:" << std::endl;
            ostream << vector_p;
        }
    }

    // capture time on end and print the time result
    auto end = std::chrono::high_resolution_clock::now();
    ostream << "Needed " << to_ms(end - start).count() << " ms to finish." << std::endl;
}

std::vector<double>
SystemSolver::backward_substitution(const Matrix &matrix_U, const std::vector<double> &result_vector,
                                    const std::vector<double> &pivots_column_indexes,
                                    const std::vector<double> &pivots_row_indexes,
                                    const int &j) {

    int rank = pivots_column_indexes.size();
    int defect = matrix_U.width - 1 - rank;
    std::stack<double, std::vector<double>> rows_indexes = std::stack<double, std::vector<double>>(pivots_row_indexes);
    std::vector<double> e(defect, 0.0);
    if (j > -1) {
        e[j] = 1;
    }
    std::vector<double> vector_x(matrix_U.width - 1);
    int last_non_used_e_row = e.size() - 1;

    for (int i = matrix_U.width - 2; i >= 0; i--) {

        if (std::find(pivots_column_indexes.begin(), pivots_column_indexes.end(), i) ==
            pivots_column_indexes.end()) {
            vector_x[i] = e[last_non_used_e_row--];
            continue;
        }

        double sum = 0;
        for (int k = vector_x.size() - 1; k >= i; k--) {
            sum += (matrix_U.get_field(k, rows_indexes.top()) * vector_x[k]);
        }

        vector_x[i] = (result_vector[rows_indexes.top()] - sum) / matrix_U.get_field(i, rows_indexes.top());
        rows_indexes.pop();
    }

    return vector_x;
}

std::pair<std::vector<double>, std::vector<double>> SystemSolver::get_pivot_indexes(const Matrix &matrix_U) {
    std::vector<double> pivots_column_indexes;
    std::vector<double> pivots_row_indexes;
    for (int x = 0; x < matrix_U.width; ++x) {
        for (int y = matrix_U.height - 1; y >= 0; --y) {
            if (std::find(pivots_row_indexes.begin(), pivots_row_indexes.end(), y) == pivots_row_indexes.end() &&
                matrix_U.get_field(x, y) != 0) {
                pivots_column_indexes.push_back(x);
                pivots_row_indexes.push_back(y);
                break;
            }
        }
    }
    return std::make_pair(pivots_column_indexes, pivots_row_indexes);
}
