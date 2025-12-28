
add_executable(LQCD LQCD.cpp LQCD.h)

target_link_libraries(LQCD PUBLIC LQED Lattice LatticeConfig plotting)
target_include_directories(LQCD PUBLIC ${matplotlib_cpp_INCLUDE_DIRS})
target_link_libraries(LQCD PUBLIC ${Python3_LIBRARIES} Python3::NumPy)
target_include_directories(LQCD PUBLIC ${PYTHON_INCLUDE_DIRS})
