//
// Created by tomanm10 on 13.12.2019.
//

#include "system_solver.hpp"
#include <algorithm>
#include <stack>

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
    ostream << matrix;

    Matrix matrix_U = decompose_lu(matrix).second;
    matrix_U.augmented = true;
    bool has_solution = false;
    for (int i = matrix_U.height - 1; i >= 0; --i) {
        if (matrix_U.get_field(matrix_U.width - 1, i) != 0) {
            for (int j = matrix_U.width - 2; j >= 0; ++j) {
                if (matrix_U.get_field(j, i) != 0) {
                    has_solution = true;
                    break;
                }
            }
            if (!has_solution) {
                break;
            }
        }
    }
    ostream << matrix_U;
    if (!has_solution) {
        ostream << "Given linear system has no solution." << std::endl;
    } else {
        ostream << "Solution of the linear system:" << std::endl;

        // find pivot indexes
        std::vector<double> pivots_column_indexes;
        std::vector<double> pivots_row_indexes;
        for (int x = 0; x < matrix_U.width - 1; ++x) {
            for (int y = matrix_U.height - 1; y >= 0; --y) {
                if (std::find(pivots_row_indexes.begin(), pivots_row_indexes.end(), y) == pivots_row_indexes.end() &&
                    matrix_U.get_field(x, y) != 0) {
                    pivots_column_indexes.push_back(x);
                    pivots_row_indexes.push_back(y);
                    break;
                }
            }
        }

        ostream << "Pivots are on columns:" << std::endl;
        ostream << pivots_column_indexes;

        // find particular solution
        std::vector<double> vector_p(matrix_U.width - 1);
        std::vector<double> b = matrix_U.get_column(matrix_U.width - 1);
        std::stack<double, std::vector<double>> rows_indexes(pivots_row_indexes);
        for (int i = matrix_U.width - 2; i >= 0; i--) {
            if (std::find(pivots_column_indexes.begin(), pivots_column_indexes.end(), i) ==
                pivots_column_indexes.end()) {
                vector_p[i] = 0;
                continue;
            }
            double sum = 0;
            for (int k = vector_p.size() - 1; k >= i; k--) {
                sum += (matrix_U.get_field(k, rows_indexes.top()) * vector_p[k]);
            }
            vector_p[i] = (b[rows_indexes.top()] - sum) / matrix_U.get_field(i, rows_indexes.top());
            rows_indexes.pop();
        }

        // find kernel if needed
        std::vector<std::vector<double>> kernel;
        int rank = pivots_column_indexes.size();
        int defect = matrix_U.width - 1 - rank;
        for (int j = 0; j < defect; ++j) {
            rows_indexes = std::stack<double, std::vector<double>>(pivots_row_indexes);
            std::vector<double> e(defect, 0.0);
            e[j] = 1;
            std::vector<double> kernel_basis_vector(matrix_U.width - 1);
            int last_non_used_e_row = e.size() - 1;
            for (int i = matrix_U.width - 2; i >= 0; i--) {
                if (std::find(pivots_column_indexes.begin(), pivots_column_indexes.end(), i) ==
                    pivots_column_indexes.end()) {
                    kernel_basis_vector[i] = e[last_non_used_e_row--];
                    continue;
                }
                double sum = 0;
                for (int k = kernel_basis_vector.size() - 1; k >= i; k--) {
                    sum += (matrix_U.get_field(k, rows_indexes.top()) * kernel_basis_vector[k]);
                }
                kernel_basis_vector[i] = (0 - sum) / matrix_U.get_field(i, rows_indexes.top());
                rows_indexes.pop();
            }
            kernel.push_back(kernel_basis_vector);
        }

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
}

std::vector<double> SystemSolver::forward_substitution(const Matrix &matrix, const std::vector<double> &result_vector) {
    std::vector<double> x(result_vector.size());
    for (int i = 0; i < result_vector.size(); i++) {
        double sum = 0;
        for (int k = 0; k < i; k++) {
            sum += (matrix.get_field(k, i) * x[k]);
        }
        x[i] = result_vector[i] - sum;
    }
    return x;
}

std::vector<double>
SystemSolver::backward_substitution(const Matrix &matrix, const std::vector<double> &result_vector) {
    std::vector<double> x(result_vector.size());
    for (int i = result_vector.size() - 1; i >= 0; i--) {
        double sum = 0;
        for (int k = result_vector.size() - 1; k >= i; k--) {
            sum += (matrix.get_field(k, i) * x[k]);
        }
        x[i] = (result_vector[i] - sum) / matrix.get_field(i, i);
    }
    return x;
}
