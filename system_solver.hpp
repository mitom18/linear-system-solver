//
// Created by tomanm10 on 13.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP
#define LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP

#include <vector>

#include "matrix.hpp"

/**
 * Class responsible for solving the system of linear equations.
 */
class SystemSolver {
private:
    /**
     * Shuffles the given matrix, so it has rows starting with 0 at the bottom.
     *
     * @param matrix matrix to be shuffled
     */
    static void shuffle_zero_rows(Matrix &matrix);

    /**
     * Performs LU decomposition for the given matrix.
     *
     * @param matrix matrix to be decomposed
     * @return std::pair of lower triangular matrix (first) and upper triangular matrix (second)
     */
    static std::pair<Matrix, Matrix> decompose_lu(const Matrix &matrix);

    /**
     * Gets the vector x from Ax = b with using backward substitution.
     *
     * @param matrix_U upper triangular matrix
     * @param result_vector vector of the desired solution
     * @param pivots_column_indexes column indexes of pivots in matrix_U
     * @param pivots_row_indexes row indexes of pivots in matrix_U
     * @param j used for finding kernel basis, determines on which non pivot field 1 is inserted
     * @return searched vector x
     */
    static std::vector<double> backward_substitution(const Matrix &matrix_U, const std::vector<double> &result_vector,
                                                     const std::vector<double> &pivots_column_indexes,
                                                     const std::vector<double> &pivots_row_indexes,
                                                     const int &j = -1);

    /**
     * Gets pair of column and row indexes of the pivots in the given upper triangular matrix.
     *
     * @param matrix_U upper triangular matrix to find pivot indexes in
     * @return std::pair of pivot column indexes (first) and pivot row indexes (second)
     */
    static std::pair<std::vector<double>, std::vector<double>> get_pivot_indexes(const Matrix &matrix_U);

public:
    /**
     * Solves the given linear system's augmented matrix and prints the solution to the output stream.
     *
     * @param ostream output stream to write to
     * @param matrix augmented matrix of the linear system
     */
    static void solve(std::ostream &ostream, const Matrix &matrix);
};

#endif //LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP
