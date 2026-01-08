add_library(
    sampleWriter STATIC
    SampleWriterBase.h
    SampleWriterJSON.h
)

set_target_properties(sampleWriter PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(sampleWriter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(sampleWriter PUBLIC nlohmann_json)