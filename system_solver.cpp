//
// Created by tomanm10 on 13.12.2019.
//

#include "system_solver.hpp"

std::pair<Matrix, Matrix> SystemSolver::decompose_lu(Matrix &matrix) {
    if (!matrix.is_square()) {
        throw std::domain_error("Matrix is not square and cannot be LU decomposed.");
    }

    int dimension = matrix.height;
    // upper triangular matrix
    Matrix matrix_U = Matrix(dimension, dimension, false);
    // lower triangular matrix
    Matrix matrix_L = Matrix(dimension, dimension, false);

    double sum = 0;
    for (int i = 0; i < dimension; i++) {

        // matrix U
        for (int j = i; j < dimension; j++) {
            // sum of L(i, k) * U(k, j)
            sum = 0;
            for (int k = 0; k < i; k++) {
                sum += (matrix_L.get_field(k, i) * matrix_U.get_field(j, k));
            }
            // set U(i, j)
            matrix_U.set_field(j, i, matrix.get_field(j, i) - sum);
        }

        // matrix L
        for (int j = i; j < dimension; j++) {
            if (i == j) {
                // 1 on diagonal
                matrix_L.set_field(i, i, 1);
            } else {
                // sum of L(j, k) * U(k, i)
                sum = 0;
                for (int k = 0; k < i; k++) {
                    sum += matrix_L.get_field(k, j) * matrix_U.get_field(i, k);
                }
                // set L(j, i)
                matrix_L.set_field(i, j, (matrix.get_field(i, j) - sum) / (matrix_U.get_field(i, i)));
            }
        }
    }
    return std::make_pair(matrix_L, matrix_U);
}

std::vector<double> SystemSolver::solve(Matrix &matrix) {
    Matrix matrix_A = matrix.get_matrix_A();
    std::vector<double> vector_b = matrix.get_column(matrix.width - 1);
    std::vector<double> solution;

    std::cout << "Matrix A:" << std::endl;
    std::cout << matrix_A;

    if (matrix_A.is_square()) {
        solution = solve_lu(matrix_A, vector_b);
    } else {
        //TODO decompose_qr
    }

    return solution;
}

std::vector<double> SystemSolver::solve_lu(Matrix &matrix_A, std::vector<double> &vector_b) {
    std::pair<Matrix, Matrix> lu = decompose_lu(matrix_A);
    Matrix matrix_L = lu.first;
    Matrix matrix_U = lu.second;

    std::cout << "Lower triangular matrix:" << std::endl;
    std::cout << matrix_L;
    std::cout << "Upper triangular matrix:" << std::endl;
    std::cout << matrix_U;

    double sum = 0;

    // find solution of Ly = b by forward substitution
    std::vector<double> y(vector_b.size());
    for (int i = 0; i < vector_b.size(); i++) {
        sum = 0;
        for (int k = 0; k < i; k++) {
            sum += (matrix_L.get_field(k, i) * y[k]);
        }
        y[i] = vector_b[i] - sum;
    }

    // find solution of Ux = y by backward substitution
    std::vector<double> x(y.size());
    for (int i = y.size() - 1; i >= 0; i--) {
        sum = 0;
        for (int k = y.size() - 1; k >= i; k--) {
            sum += (matrix_U.get_field(k, i) * x[k]);
        }
        x[i] = (y[i] - sum) / matrix_U.get_field(i, i);
    }

    return x;
}
