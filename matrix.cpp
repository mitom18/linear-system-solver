//
// Created by tomanm10 on 04.12.2019.
//

#include <iostream>
#include <iomanip>
#include <exception>
#include <algorithm>

#include "matrix.hpp"

Matrix::Matrix(const int &width, const int &height, const bool &expanded) :
        width(width), height(height), expanded(expanded) {
    data = new double[width * height](); // all elements set to 0
}

Matrix::~Matrix() {
    delete[] data;
}

Matrix::Matrix(const Matrix &rhs) :
        width(rhs.width), height(rhs.height), expanded(rhs.expanded) {
    data = new double[width * height]();
    std::copy(rhs.data, rhs.data + rhs.width * rhs.height, data);
}

Matrix::Matrix(Matrix &&rhs) noexcept :
        width(rhs.width), height(rhs.height), expanded(rhs.expanded) {
    data = new double[width * height]();
    std::move(rhs.data, rhs.data + rhs.width * rhs.height, data);
}

Matrix &Matrix::operator=(const Matrix &rhs) {
    Matrix temp(rhs);
    swap(temp);
    return *this;
}

Matrix &Matrix::operator=(Matrix &&rhs) noexcept {
    swap(rhs);
    return *this;
}

void Matrix::swap(Matrix &rhs) {
    std::swap(width, rhs.width);
    std::swap(height, rhs.height);
    std::swap(expanded, rhs.expanded);
    std::swap(data, rhs.data);
}

size_t Matrix::index(const int &x, const int &y) const {
    return x + width * y;
}

double Matrix::get_field(const int &x, const int &y) const {
    return data[index(x, y)];
}

void Matrix::set_field(const int &x, const int &y, double value) {
    data[index(x, y)] = value;
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

void Matrix::set_row(const int &y, std::vector<double> values) {
    if (values.size() != width) {
        throw std::domain_error("not right number of new values given");
    }
    for (int x = 0; x < width; ++x) {
        data[index(x, y)] = values[x];
    }
}

void Matrix::set_column(const int &x, std::vector<double> values) {
    if (values.size() != height) {
        throw std::domain_error("not right number of new values given");
    }
    for (int y = 0; y < height; ++y) {
        data[index(x, y)] = values[y];
    }
}

bool Matrix::is_square() const {
    return height == width;
}

Matrix Matrix::get_matrix_A() const {
    Matrix matrix_A = Matrix(width - 1, height, false);
    matrix_A.expanded = false;
    for (int x = 0; x < width - 1; ++x) {
        matrix_A.set_column(x, get_column(x));
    }
    return matrix_A;
}

Matrix Matrix::get_transposition() const {
    Matrix transposition = Matrix(height, width, expanded);
    for (int y = 0; y < height; ++y) {
        transposition.set_column(y, get_row(y));
    }
    return transposition;
}

std::ostream &operator<<(std::ostream &ostream, const Matrix &matrix) {
    ostream << "Matrix:" << std::endl;
    ostream << std::setprecision(2);
    for (int y = 0; y < matrix.height; ++y) {
        ostream << "( ";
        for (int x = 0; x < matrix.width; ++x) {
            if (matrix.expanded && x == matrix.width - 1) ostream << "| ";
            ostream << matrix.get_field(x, y) << " ";
        }
        ostream << ")" << std::endl;
    }
    return ostream;
}

std::ostream &operator<<(std::ostream &ostream, const std::vector<double> &vector) {
    ostream << "Vector ( ";
    for (auto n : vector) {
        ostream << n << " ";
    }
    ostream << ")" << std::endl;
    return ostream;
}

Matrix MatrixCreator::parse_from_cmd_line(std::ostream &ostream, std::istream &istream) {
    int width;
    int height;
    ostream << "Enter width of the linear system matrix: ";
    istream >> width;
    ostream << "Enter height of the linear system matrix: ";
    istream >> height;

    Matrix matrix(width, height, true);

    for (int y = 0; y < height; ++y) {
        ostream << "Enter " << y + 1 << ". row of the matrix:" << std::endl;
        for (int x = 0; x < width; ++x) {
            double d;
            istream >> d;
            matrix.set_field(x, y, d);
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

    Matrix matrix(width, height, true);

    for (int y = 0; y < height; ++y) {
        std::getline(file, line);
        line_stream << line;
        for (int x = 0; x < width; ++x) {
            double d;
            line_stream >> d;
            matrix.set_field(x, y, d);
        }
    }

    return matrix;
}
