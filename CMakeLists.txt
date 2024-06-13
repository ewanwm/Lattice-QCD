cmake_minimum_required(VERSION 3.0.0)

project(LQCD VERSION 0.1.0 LANGUAGES CXX)

find_package(Python3 3.4 COMPONENTS Interpreter NumPy REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message("PYTHON_LIBRARY :${PYTHON_LIBRARY}")
message("PYTHON_INCLUDE_DIR :${PYTHON_INCLUDE_DIR}")
message("PYTHON_SITELIB: ${Python_SITELIB}")

#include_directories(${PYTHON_LIBRARY})
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(src)
add_subdirectory(app)

