//
// Created by tomanm10 on 04.12.2019.
//

#include <iostream>
#include <limits>

#include "system_solver.hpp"

Matrix::Matrix(const int &width, const int &height) : width(width), height(height) {
    data = new double[width * height];
}

size_t Matrix::index(const int &x, const int &y) const {
    return x + width * y;
}

double Matrix::get_field(const int &x, const int &y) const {
    return data[index(x, y)];
}

Matrix MatrixCreator::parse_from_cmd_line(std::ostream &ostream, std::istream &istream) {
    int width;
    int height;
    ostream << "Enter width of the linear system matrix: ";
    istream >> width;
    ostream << "Enter height of the linear system matrix: ";
    istream >> height;

    Matrix matrix(width, height);

    for (int y = 0; y < height; ++y) {
        ostream << "Enter " << y+1 << ". row of the matrix:" << std::endl;
        for (int x = 0; x < width; ++x) {
            double d;
            istream >> d;
            matrix.data[matrix.index(x, y)] = d;
        }
        istream.clear();
        istream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return matrix;
}
