
add_library(matplotlib INTERFACE)

target_link_libraries(matplotlib INTERFACE ${PYTHON_LIBRARIES} Python3::NumPy)

target_include_directories(matplotlib INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

