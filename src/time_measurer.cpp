//
// Created by mprotsyk on 08.02.22.
//

#include "time_measurer.h"


TimeMeasurer::TimeMeasurer(std::string _title): title(std::move(_title)) {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    start = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
}


TimeMeasurer::~TimeMeasurer() {
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    std::cout << title << " " << microseconds << "ms" << std::endl;
}