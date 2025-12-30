
add_library(
    sampling STATIC
    SamplerBase.h
    SamplerMetropolisHastings.h SamplerMetropolisHastings.cpp
    SampleWriterBase.h
)

target_include_directories(sampling PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(sampling PUBLIC dtypes LatticeConfig nlohmann_json)