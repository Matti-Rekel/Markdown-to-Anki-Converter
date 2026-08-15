add_library(FileHandler FileHandler.cpp)

target_include_directories(FileHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(FileHandler Formatter)
