//
// Created by tomanm10 on 04.12.2019.
//

#include <iostream>
#include <iomanip>
#include <exception>

#include "matrix.hpp"

Matrix::Matrix(const int &width, const int &height) : width(width), height(height) {
    data = new double[width * height];
}

size_t Matrix::index(const int &x, const int &y) const {
    return x + width * y;
}

double Matrix::get_field(const int &x, const int &y) const {
    return data[index(x, y)];
}

std::vector<double> Matrix::get_row(const int &y) const {
    std::vector<double> row;
    row.reserve(width);
    for (int x = 0; x < width; ++x) {
        row.push_back(get_field(x, y));
    }
    return row;
}

std::vector<double> Matrix::get_column(const int &x) const {
    std::vector<double> column;
    column.reserve(height);
    for (int y = 0; y < height; ++y) {
        column.push_back(get_field(x, y));
    }
    return column;
}

std::ostream &operator<<(std::ostream &ostream, const Matrix &matrix) {
    ostream << "Matrix:" << std::endl;
    ostream << std::setprecision(2);
    for (int y = 0; y < matrix.height; ++y) {
        ostream << "( ";
        for (int x = 0; x < matrix.width; ++x) {
            if (x == matrix.width - 1) ostream << " | ";
            ostream << matrix.get_field(x, y) << " ";
        }
        ostream << ")" << std::endl;
    }
    return ostream;
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
        ostream << "Enter " << y + 1 << ". row of the matrix:" << std::endl;
        for (int x = 0; x < width; ++x) {
            double d;
            istream >> d;
            matrix.data[matrix.index(x, y)] = d;
        }
    }

    return matrix;
}

Matrix MatrixCreator::parse_from_txt_file(std::ostream &ostream, std::istream &istream) {
    ostream << "Choose file from shown below:" << std::endl;
    std::ifstream file = FileReader::choose_file(ostream, istream);

    std::string line;
    std::getline(file, line);
    std::stringstream line_stream;
    line_stream << line;
    int width, height;
    line_stream >> width >> height;
    if (!file || !line_stream) {
        throw std::domain_error("Failed to load matrix from file.");
    }

    Matrix matrix(width, height);

    for (int y = 0; y < height; ++y) {
        std::getline(file, line);
        line_stream << line;
        for (int x = 0; x < width; ++x) {
            double d;
            line_stream >> d;
            matrix.data[matrix.index(x, y)] = d;
        }
    }

    return matrix;
}
