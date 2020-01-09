//
// Created by tomanm10 on 04.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_MATRIX_HPP
#define LINEAR_SYSTEM_SOLVER_MATRIX_HPP

#include <string>
#include <vector>

#include "utils.hpp"

/**
 * Struct representing matrix of the linear system.
 */
struct Matrix {
    int width;
    int height;
    double* data{};
    bool augmented;

    /**
     * @param x
     * @param y
     * @return index of element on [x,y] coords in the matrix
     */
    size_t index(const int &x, const int &y) const;

    /**
     * Matrix constructor
     * @param width Number of vectors in the matrix
     * @param height Dimension of vectors in the matrix
     * @param augmented true if the matrix is augmented (last column is vector b), false otherwise
     */
    Matrix(const int &width, const int &height, const bool &augmented);

    /**
     * Matrix destructor
     */
    virtual ~Matrix();

    /**
     * Copy constructor
     * @param rhs
     */
    Matrix(const Matrix &rhs);

    /**
     * Move constructor
     * @param rhs
     */
    Matrix(Matrix &&rhs) noexcept;

    /**
     * Copy assignment
     * @param rhs
     * @return
     */
    Matrix& operator=(const Matrix &rhs);

    /**
     * Move assignment
     * @param rhs
     * @return
     */
    Matrix& operator=(Matrix &&rhs) noexcept;

    /**
     * Swaps contents of the two matrices
     * @param rhs
     */
    void swap(Matrix &rhs);

    /**
     * @param x
     * @param y
     * @return element on [x,y] coords in the matrix
     */
    double get_field(const int &x, const int &y) const;

    /**
     * Sets value of element on [x,y] coords in the matrix.
     * @param x
     * @param y
     * @param value to be inserted into the matrix
     */
    void set_field(const int &x, const int &y, double value);

    /**
     * @param y
     * @return y-th row of the matrix as vector of references to elements
     */
    std::vector<double> get_row(const int &y) const;

    /**
     * Sets y-th row of the matrix to be given vector of values.
     * @param y
     * @param values inserted to the given row
     */
    void set_row(const int &y, std::vector<double> values);

    /**
     * @param x
     * @return x-th column of the matrix as vector of references to elements
     */
    std::vector<double> get_column(const int &x) const;

    /**
     * Sets x-th column of the matrix to be given vector of values.
     * @param x
     * @param values inserted to the given column
     */
    void set_column(const int &x, std::vector<double> values);

    /**
     * Checks if the matrix is square (size n * n).
     * @return true if matrix is square, false otherwise
     */
    bool is_square() const;

    /**
     * Copies the matrix and removes the vector b from the copy. The modified copy is returned.
     * @return matrix A from the augmented linear matrix
     */
    Matrix get_matrix_A() const;

    /**
     * Copies the matrix and transposes it. The modified copy is returned.
     * @return transposition of the matrix
     */
    Matrix get_transposition() const;
};

Matrix operator*(const Matrix &A, const Matrix &B);

Matrix operator+(const Matrix &A, const Matrix &B);

Matrix operator-(const Matrix &A, const Matrix &B);

std::ostream& operator<<(std::ostream &ostream, const Matrix &matrix);

std::ostream& operator<<(std::ostream &ostream, const std::vector<double> &vector);

/**
 * Class responsible for creating the matrix structs
 */
class MatrixCreator {
public:
    /**
     * Parses matrix from command line. Provides basic user communication.
     * @param ostream
     * @param istream
     * @return Matrix
     */
    static Matrix parse_from_cmd_line(std::ostream &ostream, std::istream &istream);

    /**
     * Parses matrix from txt file. Provides also the file choose.
     * @param ostream
     * @param istream
     * @return Matrix
     */
    static Matrix parse_from_txt_file(std::ostream &ostream, std::istream &istream);

    /**
     * Creates identity matrix of given dimension.
     * @param dimension
     * @return matrix of identity
     */
    static Matrix get_identity(const int &dimension);
};

#endif //LINEAR_SYSTEM_SOLVER_MATRIX_HPP
