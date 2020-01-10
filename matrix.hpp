//
// Created by tomanm10 on 04.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_MATRIX_HPP
#define LINEAR_SYSTEM_SOLVER_MATRIX_HPP

#include <string>
#include <vector>

#include "utils.hpp"

/**
 * Struct representing matrix.
 * <p>
 * If augmented is set to true, than the matrix represents system of linear equations.
 */
struct Matrix {
    int width;
    int height;
    double *data{};
    bool augmented;

    /**
     * @param x index of the column
     * @param y index of the row
     * @return index of element on [x,y] coords in the matrix
     */
    size_t index(const int &x, const int &y) const;

    /**
     * Matrix constructor.
     *
     * @param width number of vectors in the matrix
     * @param height dimension of vectors in the matrix
     * @param augmented true if the matrix is augmented (last column is vector b), false otherwise
     */
    Matrix(const int &width, const int &height, const bool &augmented);

    /**
     * Matrix destructor.
     */
    virtual ~Matrix();

    /**
     * Copy constructor.
     *
     * @param rhs matrix to copy from
     */
    Matrix(const Matrix &rhs);

    /**
     * Move constructor.
     *
     * @param rhs matrix to move from
     */
    Matrix(Matrix &&rhs) noexcept;

    /**
     * Copy assignment.
     *
     * @param rhs matrix to copy from
     * @return reference to this
     */
    Matrix &operator=(const Matrix &rhs);

    /**
     * Move assignment.
     *
     * @param rhs matrix to move from
     * @return reference to this
     */
    Matrix &operator=(Matrix &&rhs) noexcept;

    /**
     * Swaps contents of the two matrices.
     *
     * @param rhs
     */
    void swap(Matrix &rhs);

    /**
     * @param x index of the column in which the field is (zero based)
     * @param y index of the row in which the field is (zero based)
     * @return element on [x,y] coords in the matrix
     */
    double get_field(const int &x, const int &y) const;

    /**
     * Sets value of element on [x,y] coords in the matrix.
     *
     * @param x index of the column in which the field is (zero based)
     * @param y index of the row in which the field is (zero based)
     * @param value double to be inserted into the matrix
     */
    void set_field(const int &x, const int &y, double value);

    /**
     * @param y index of the row to be returned (zero based)
     * @return y-th row of the matrix as vector of elements
     */
    std::vector<double> get_row(const int &y) const;

    /**
     * Sets y-th row of the matrix to be given vector of values.
     *
     * @param y index of the row to be set (zero based)
     * @param values vector of doubles to be inserted in the given column
     */
    void set_row(const int &y, std::vector<double> values);

    /**
     * @param x index of the column to be returned (zero based)
     * @return x-th column of the matrix as vector of elements
     */
    std::vector<double> get_column(const int &x) const;

    /**
     * Sets x-th column of the matrix to be given vector of values.
     *
     * @param x index of the column to be set (zero based)
     * @param values vector of doubles to be inserted in the given column
     */
    void set_column(const int &x, std::vector<double> values);

    /**
     * Checks if the matrix is square (size n * n).
     *
     * @return true if matrix is square, false otherwise
     */
    bool is_square() const;

    /**
     * Copies the matrix and removes the vector b from the copy. The modified copy is returned.
     * @return Matrix matrix A from the augmented linear matrix
     */
    Matrix get_matrix_A() const;

    /**
     * Copies the matrix and transposes it. The modified copy is returned.
     *
     * @return Matrix transposition of the matrix
     */
    Matrix get_transposition() const;

    /**
     * Executes modifying lambda function for each field of the matrix.
     *
     * @tparam T
     * @param lambda function
     */
    template<typename T>
    void foreach_field(T &&lambda) {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                set_field(x, y, lambda(x, y, get_field(x, y)));
            }
        }
    };
};

Matrix operator*(const Matrix &A, const Matrix &B);

Matrix operator+(const Matrix &A, const Matrix &B);

Matrix operator-(const Matrix &A, const Matrix &B);

std::ostream &operator<<(std::ostream &ostream, const Matrix &matrix);

std::ostream &operator<<(std::ostream &ostream, const std::vector<double> &vector);

/**
 * Class responsible for creating the matrix structs.
 */
class MatrixCreator {
public:
    /**
     * Parses matrix from command line. Provides basic user communication.
     *
     * @param ostream output stream to write information to
     * @param istream input stream to read from
     * @return Matrix read from input stream
     */
    static Matrix parse_from_cmd_line(std::ostream &ostream, std::istream &istream);

    /**
     * Parses matrix from txt file. Provides also the file choose.
     *
     * @param ostream output stream to write information to
     * @param istream input stream to read from
     * @return Matrix read from input stream
     */
    static Matrix parse_from_txt_file(std::ostream &ostream, std::istream &istream);

    /**
     * Creates identity matrix with given dimension n. (size n * n; 1 in fields on diagonal, 0 in all other fields)
     *
     * @param dimension size of the returned matrix
     * @return Matrix of identity
     */
    static Matrix get_identity(const int &dimension);
};

#endif //LINEAR_SYSTEM_SOLVER_MATRIX_HPP
