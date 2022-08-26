cmake_minimum_required(VERSION 3.20.0)
project(Graphics)

set(CMAKE_CXX_STANDARD 17)
link_libraries(glfw)
link_libraries(glad)
add_library(Graphics ShaderData.cpp ShaderData.h Display.h Display.cpp InputFn.cpp InputFn.h)
message("This file was reached by cmake")
message("The current source dir is " ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(Graphics PRIVATE ${PROJECT_SOURCE_DIR}/libs/glfw/include ${PROJECT_SOURCE_DIR}/libs/glad/include)