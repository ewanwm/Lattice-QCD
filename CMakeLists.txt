cmake_minimum_required(VERSION 3.0.0)

project(LQCD VERSION 0.1.0 LANGUAGES CXX)

find_package(matplotlib_cpp REQUIRED TRUE)
find_package(nlohmann_json REQUIRED TRUE)

find_package(Python3 COMPONENTS Development NumPy)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
add_subdirectory(app)

