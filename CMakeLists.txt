cmake_minimum_required(VERSION 3.21)
project(matrix)

set(CMAKE_CXX_STANDARD 20)

include_directories(inc)

add_executable(matrix src/main.cpp inc/matrix.h src/time_measurer.cpp inc/time_measurer.h inc/benchmarks.h)
