cmake_minimum_required(VERSION 3.20)
project(PathPlanner)

set(CMAKE_CXX_STANDARD 17)

add_executable(PathPlanner main.cpp libs/MatrixMath/MatrixMath.h)
