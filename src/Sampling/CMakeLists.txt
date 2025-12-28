
add_library(
    sampling STATIC
    SamplerBase.h
    SamplerMetropolisHastings.h SamplerMertopolisHastings.cpp
    SampleWriterBase.h
)

target_include_directories(sampling PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(sampling PUBLIC dtypes LatticeConfig )