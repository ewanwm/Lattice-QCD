
add_library(matplotlib INTERFACE)

target_link_libraries(matplotlib INTERFACE ${Python3_LIBRARIES} Python3::NumPy)

target_include_directories(matplotlib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")



add_library(plotting plottingUtils.h)
set_target_properties(plotting PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(plotting matplotlib)

