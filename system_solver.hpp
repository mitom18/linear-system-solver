//
// Created by tomanm10 on 13.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP
#define LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP

#include <vector>

#include "matrix.hpp"

/**
 * Class responsible for solving the linear system.
 */
class SystemSolver {
private:
    // TODO https://en.wikipedia.org/wiki/LU_decomposition
    /**
     * Performs LU decomposition for the given square matrix.
     * @param matrix square matrix A
     */
    static std::pair<Matrix, Matrix> decompose_lu(Matrix &matrix);

    /**
     * Solves the given linear system with LU decomposition.
     * @param matrix_A Square matrix
     * @param vector_b Right most vector of the expanded matrix
     * @return solution of the linear system as vector
     */
    static std::vector<double> solve_lu(Matrix &matrix_A, std::vector<double> &vector_b);

    // TODO https://en.wikipedia.org/wiki/QR_decomposition
    static void decompose_qr(Matrix &matrix);

public:
    /**
     * Solves the given linear system's expanded matrix.
     * @param matrix expanded matrix of the linear system
     * @return solution of the linear system defined with given matrix as vector
     */
    // TODO https://stackoverflow.com/questions/20181940/most-efficient-way-to-solve-a-system-of-linear-equations
    static std::vector<double> solve(Matrix &matrix);
};

#endif //LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP
