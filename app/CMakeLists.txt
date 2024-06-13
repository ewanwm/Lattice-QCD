
add_executable(LQCD LQCD.cpp LQCD.h)

target_link_libraries(LQCD PUBLIC matplotlib LQED Lattice SpinModel)