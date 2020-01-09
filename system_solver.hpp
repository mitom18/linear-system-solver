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
    /**
     * Performs LU decomposition for the given square matrix.
     * @param matrix Matrix A
     */
    static std::pair<Matrix, Matrix> decompose_lu(const Matrix &matrix);

    /**
     * Gets the vector x from Ax = b with using forward substitution.
     * @param matrix A
     * @param result_vector b
     * @return searched vector x
     */
    static std::vector<double> forward_substitution(const Matrix &matrix, const std::vector<double> &result_vector);

    /**
     * Gets the vector x from Ax = b with using backward substitution.
     * @param matrix A
     * @param result_vector b
     * @return searched vector x
     */
    static std::vector<double> backward_substitution(const Matrix &matrix, const std::vector<double> &result_vector);

public:
    /**
     * Solves the given linear system's augmented matrix and prints the solution to output stream.
     * @param ostream output stream to write to
     * @param matrix augmented matrix of the linear system
     */
    static void solve(std::ostream &ostream, const Matrix &matrix);
};

#endif //LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP
