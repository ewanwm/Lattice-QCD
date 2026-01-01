
add_library(plotting plottingUtils.h matplotlibcpp.h)
set_target_properties(plotting PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(plotting PUBLIC ${Python3_LIBRARIES} Python3::NumPy)

message("Python3_INCLUDE_DIRS: ${Python3_INCLUDE_DIRS}")
message("Python3_LIBRARIES: ${Python3_LIBRARIES}")
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(plotting ${PYTHON_LIBRARIES})

target_include_directories(plotting PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${Python3_INCLUDE_DIRS}")
   