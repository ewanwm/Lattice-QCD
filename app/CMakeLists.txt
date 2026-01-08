
add_executable(LQCD LQCD.cpp)

target_link_libraries(LQCD PUBLIC Lattice LatticeConfig plotting sampling)
target_include_directories(LQCD PUBLIC ${PYTHON_INCLUDE_DIRS})
