//
// Created by mprotsyk on 08.02.22.
//

#ifndef MATRIX_TIME_MEASURER_H
#define MATRIX_TIME_MEASURER_H

#include <atomic>
#include <chrono>
#include <string>
#include <iostream>


class TimeMeasurer {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::string title;
public:
    explicit TimeMeasurer(std::string _title);
    ~TimeMeasurer();
};

#endif //MATRIX_TIME_MEASURER_H
