cmake_minimum_required(VERSION 3.20)
project(PathPlanner)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/dir/release)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In Source Builds are not allowed")
endif()


message("The Project folder is located at " ${PROJECT_SOURCE_DIR})
message("The build folder is located at " ${PROJECT_BINARY_DIR})





message("The build folder is located at " ${PROJECT_BINARY_DIR})

add_subdirectory(libs/glad)
add_subdirectory(libs/glfw)
add_subdirectory(libs/glm)
add_subdirectory(src)

add_executable(PathPlanner main.cpp libs/MatrixMath/MatrixMath.h libs/stb/stb_image.h)




target_link_libraries(PathPlanner glad glfw Graphics Map)