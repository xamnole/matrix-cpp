#include <iostream>

#include "matrix.h"
#include "benchmarks.h"


int main() {
    //! WARNING: here I won't print all the results, but only the first matrix
    //! (some operation may not change it and instead create a new one)
    size_t height1, width1;
    std::cout << "Enter the width and the height of the first matrix: ";
    std::cin >> height1 >> width1;

    size_t width2;
    std::cout << "Enter the width of the second matrix: ";
    std::cin >> width2;

    Matrix<double> first(height1, width1, 1.0);
    Matrix<double> second(width1, width2, 1.0);

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