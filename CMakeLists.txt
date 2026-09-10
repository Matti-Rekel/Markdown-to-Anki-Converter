cmake_minimum_required(VERSION 3.20)

project(Converter)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

target_compile_features(Converter PRIVATE cxx_std_26)

target_compile_options(Converter PRIVATE
    -fcontracts
    -fcontract-evaluation-semantic=enforce
)

target_link_options(Converter PRIVATE
    -fcontracts
)
