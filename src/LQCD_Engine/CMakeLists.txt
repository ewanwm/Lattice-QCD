add_library(dtypes STATIC dtypes.h)
set_target_properties(dtypes PROPERTIES LINKER_LANGUAGE CXX)
add_library(Lattice STATIC Lattice.h Lattice.cpp)
add_library(MagneticSpinModel STATIC MagneticSpinModel.h MagneticSpinModel.cpp)
add_library(LQED STATIC LQED.cpp LQED.h)

add_library(
    LatticeConfig STATIC 
    ModelBase.h
    ModelBase2D.h ModelBase2D.cpp
    MagneticSpinModel.h MagneticSpinModel.cpp
    ScalarFieldModel.h ScalarFieldModel.cpp
)

target_include_directories(dtypes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(Lattice PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(LatticeConfig PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(LQED PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
