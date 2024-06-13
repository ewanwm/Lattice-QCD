
add_library(Lattice STATIC Lattice.h Lattice.cpp)
add_library(SpinModel STATIC SpinModel.h SpinModel.cpp)
add_library(LQED STATIC LQED.cpp LQED.h)

target_include_directories(Lattice PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(SpinModel PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(LQED PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
