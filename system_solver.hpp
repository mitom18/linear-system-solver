//
// Created by tomanm10 on 04.12.2019.
//

#ifndef LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP
#define LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP

#include <string>

/**
 * Struct representing linear system matrix
 */
struct Matrix {
    int width;
    int height;
    double* data;

    /**
     * Matrix constructor.
     * @param width Number of vectors in the matrix
     * @param height Dimension of vectors in the matrix
     */
    Matrix(const int &width, const int &height);

    /**
     * @param x
     * @param y
     * @return index of element on [x,y] coords in the matrix
     */
    size_t index(const int &x, const int &y) const;

    /**
     * @param x
     * @param y
     * @return element on [x,y] coords in the matrix
     */
    double get_field(const int &x, const int &y) const;
};

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
};

#endif //LINEAR_SYSTEM_SOLVER_SYSTEM_SOLVER_HPP
