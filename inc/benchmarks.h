//
// Created by mprotsyk on 08.02.22.
//

#ifndef MATRIX_BENCHMARKS_H
#define MATRIX_BENCHMARKS_H

#include <functional>

#include "matrix.h"
#include "time_measurer.h"

static constexpr std::pair<size_t, size_t> printable_matrix = {10, 10};


template <class T>
void perform_benchmark(Matrix<T>& matrix, const std::string& title, std::function<void(Matrix<T>&)> op) {
    std::cout << "---------------------" << std::endl;
    std::cout << "Performing benchmark: " << std::endl;
    {
        TimeMeasurer measurer(title);
        op(matrix);
    }

    if (matrix.get_height() <= printable_matrix.first && matrix.get_width() <= printable_matrix.second) {
        std::cout << "The given matrix after performing the benchmark: " << std::endl;
        std::cout << matrix.to_string(6, 3) << std::endl;
    } else {
        std::cout << "The matrix is too big to be printed" << std::endl;
    }

    std::cout << "---------------------" << std::endl;
}


#endif //MATRIX_BENCHMARKS_H
