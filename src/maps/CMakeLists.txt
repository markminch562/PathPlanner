cmake_minimum_required(VERSION 3.20.0)
project(Map)

set(CMAKE_CXX_STANDARD 17)
add_library(Map include/Map.h src/Map.cpp)
target_include_directories(Map PUBLIC ./include)