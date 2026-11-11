cmake_minimum_required(VERSION 3.20)

project(Converter)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

add_subdirectory(src)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
)

FetchContent_MakeAvailable(googletest)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()