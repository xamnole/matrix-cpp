//
// Created by mprotsyk on 08.02.22.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <iostream>
#include <type_traits>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <iomanip>
#include <functional>


template<class T>
class Matrix {
private:
    size_t height;
    size_t width;
    T* data;


public:

    Matrix(size_t _height, size_t _width, T value, bool fill=true);
    Matrix(const Matrix<T>& matrix);
    Matrix(size_t _height, size_t _width, bool fill=true);

    size_t get_height();
    size_t get_width();

    Matrix<T> get_transpose();


    Matrix<T> operator* (T scalar);
    Matrix<T> operator+ (T scalar);
    Matrix<T> operator- (T scalar);
    Matrix<T> operator/ (T scalar);

    // performs the given operation on every element of matrix
    Matrix<T>& map(std::function<T(T)> op);
    Matrix<T>& operator*= (T scalar);
    Matrix<T>& operator+= (T scalar);
    Matrix<T>& operator-= (T scalar);
    Matrix<T>& operator/= (T scalar);

    Matrix<T>& operator=(const Matrix<T>& matrix);

    // creates identity matrix of the given size
    static Matrix<T> create_identity(size_t size);


    Matrix<T> operator* (const Matrix<T>& matrix);
    Matrix<T> operator+ (const Matrix<T>& matrix);
    Matrix<T> operator- (const Matrix<T>& matrix);

    // creates a matrix with values equal to the
    // result of given operation performed on every pair of respective elements
    Matrix<T>& matrix_operation(const Matrix<T>& matrix, std::function<T(T,T)> op);
    Matrix<T>& operator+= (const Matrix<T>& matrix);
    Matrix<T>& operator-= (const Matrix<T>& matrix);

    T& get(size_t row, size_t column);

    ~Matrix();

    // calculates sum of every row and returns the vector with respective values
    std::vector<T> get_row_sums();
    // the same but for columns
    std::vector<T> get_column_sums();

    // converts matrix to string representation (maximum number of digits which will be printed)
    std::string to_string(int digits, int precision);

};


template<class T>
Matrix<T>::Matrix(size_t _height, size_t _width, T value, bool fill): height(_height), width(_width) {
    data = new T[height * width];
    if (fill) {
        std::fill(data,data + height * width, value);
    }
}


template<class T>
size_t  Matrix<T>::get_height() {
    return height;
}


template<class T>
size_t Matrix<T>::get_width() {
    return width;
}


template<class T>
Matrix<T> Matrix<T>::get_transpose() {
    Matrix<T> transposed(width, height);
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            transposed.get(j, i) = get(i, j);
        }
    }
    return transposed;
}


template<class T>
Matrix<T>& Matrix<T>::map(std::function<T(T)> op) {
    for (size_t i = 0; i < width * height; i++) {
        data[i] = op(data[i]);
    }
    return *this;
}


template<class T>
Matrix<T> Matrix<T>::operator* (T scalar) {
    Matrix new_matrix;
    new_matrix *= scalar;
    return new_matrix;
}


template<class T>
Matrix<T> Matrix<T>::operator+ (T scalar) {
    Matrix new_matrix;
    new_matrix += scalar;
    return new_matrix;
}


template<class T>
Matrix<T> Matrix<T>::operator- (T scalar) {
    Matrix new_matrix;
    new_matrix -= scalar;
    return new_matrix;
}


template<class T>
Matrix<T> Matrix<T>::operator/ (T scalar) {
    Matrix new_matrix;
    new_matrix /= scalar;
    return new_matrix;
}


template<class T>
Matrix<T>& Matrix<T>::operator*= (T scalar) {
    return map([scalar](T val){return val * scalar;});
}


template<class T>
Matrix<T>& Matrix<T>::operator+= (T scalar) {
    return map([scalar](T val){return val + scalar;});
}


template<class T>
Matrix<T>& Matrix<T>::operator-= (T scalar) {
    return map([scalar](T val){return val - scalar;});
}


template<class T>
Matrix<T>& Matrix<T>::operator/= (T scalar) {
    return map([scalar](T val){return val / scalar;});
}


template<class T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    data = new T[matrix.height * matrix.width];
    height = matrix.height;
    width = matrix.width;
    std::copy(matrix.data, matrix.data + width * height, data);
}


template<class T>
Matrix<T>::Matrix(size_t _height, size_t _width, bool fill): Matrix(_height, _width, 0, fill) {}


template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix) {
    if (&matrix == this) {
        return *this;
    }
    data = new T[matrix.height * matrix.width];
    height = matrix.height;
    width = matrix.width;
    std::copy(matrix.data, matrix.data + width * height, data);
    return *this;
}


template<class T>
Matrix<T> Matrix<T>::create_identity(size_t size) {
    Matrix<T> matrix(size, size);
    for (size_t i = 0; i < size; i++) {
        matrix.get(i, i) = 1;
    }
    return matrix;
}


template<class T>
Matrix<T>& Matrix<T>::matrix_operation(const Matrix<T>& matrix, std::function<T(T,T)> op) {
    if (matrix.width != width || matrix.height != height) {
        throw std::runtime_error("Can't add matrices of different size");
    }

    for (size_t i = 0; i < height * width; i++) {
        data[i] = op(data[i], matrix.data[i]);
    }

    return *this;
}


template<class T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& matrix) {
    if (width != matrix.height) {
        throw std::runtime_error("Can't multiply the given matrices (invalid shapes)");
    }
    Matrix<T> prod_matrix(height, matrix.width);
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < matrix.width; j++) {
            T& cell = prod_matrix.get(i, j);
            for (size_t pos = 0; pos < width; pos++) {
                cell += data[width * i + pos] * matrix.data[pos * matrix.width + j];
            }
        }
    }

    return prod_matrix;

}



template<class T>
Matrix<T>& Matrix<T>::operator+= (const Matrix<T>& matrix) {

    return matrix_operation(matrix, [](T val1, T val2) {return val1 + val2;});

}
template<class T>
Matrix<T>& Matrix<T>::operator-= (const Matrix<T>& matrix) {

    return matrix_operation(matrix, [](T val1, T val2) {return val1 - val2;});

}


template<class T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& matrix) {
    Matrix new_matrix;
    new_matrix += matrix;
    return new_matrix;

}


template<class T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& matrix) {
    Matrix new_matrix;
    new_matrix -= matrix;
    return new_matrix;

}


template<class T>
T& Matrix<T>::get(size_t row, size_t column) {
    if (row >= height || column >= width) {
        throw std::runtime_error("Cell is out of range");
    }
    return data[row * width + column];
}


template<class T>
Matrix<T>::~Matrix() {
    delete[] data;
}


template<class T>
std::vector<T> Matrix<T>::get_row_sums() {
    std::vector<T> sums(height, 0);
    size_t current_index = 0;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            sums[i] += data[current_index];
            current_index++;
        }
    }
    return sums;
}


template<class T>
std::vector<T> Matrix<T>::get_column_sums() {
    std::vector<T> sums(width, 0);
    for (size_t i = 0; i < width; i++) {
        size_t current_index = i;
        for (size_t j = 0; j < height; j++) {
            sums[i] += data[current_index];
            current_index += width;
        }
    }
    return sums;
}


template<class T>
std::string Matrix<T>::to_string(int digits, int precision){
    std::ostringstream stream;

    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            stream
                    << "["
                    << std::setw(digits + 1)
                    << std::setprecision(precision)
                    << data[i * width + j]
                    << "]";
        }
        stream << std::endl;
    }

    return stream.str();
}


#endif //MATRIX_MATRIX_H
