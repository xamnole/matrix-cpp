#include <iostream>

#include "matrix.h"
#include "benchmarks.h"

constexpr std::pair<size_t, size_t> FIRST_SHAPE = {1000, 1000};
constexpr size_t WIDTH_SECOND = 10;


int main() {
    //! WARNING: here I won't print all the results, but only the first matrix
    //! (some operation may not change it and instead create a new one)

    Matrix<double> first(FIRST_SHAPE.first, FIRST_SHAPE.second, 1.0);
    Matrix<double> second(FIRST_SHAPE.second, WIDTH_SECOND, 1.0);

    perform_benchmark<double>(
            first, "Adding a scalar: ",
            [](Matrix<double>& matrix){matrix += 1;}
                              );
    perform_benchmark<double>(
            first, "Dividing by a scalar: ",
            [](Matrix<double>& matrix){matrix /= 2;}
                              );
    perform_benchmark<double>(
            first, "Multiplying by a scalar: ",
            [](Matrix<double>& matrix){matrix *= 2;}
                              );
    perform_benchmark<double>(
            first, "Multiplying the matrices: ",
            [second](Matrix<double>& matrix){matrix * second;}
            );

    perform_benchmark<double>(
            first, "Calculating sum of rows: ",
            [](Matrix<double>& matrix){
                matrix.get_row_sums();
            }
    );

    perform_benchmark<double>(
            first, "Calculating sum of columns: ",
            [](Matrix<double>& matrix){
                matrix.get_column_sums();
            }
    );

    perform_benchmark<double>(
            first, "Adding a matrix to itself: ",
            [](Matrix<double>& matrix){
                matrix += matrix;
            }
    );

    perform_benchmark<double>(
            first, "Creating a transpose: ",
            [](Matrix<double>& matrix){
                matrix.get_transpose();
            }
    );

    return 0;
}