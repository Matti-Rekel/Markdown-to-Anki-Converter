add_library(FileHandler FileInput.cpp AnkiWriter.cpp)

target_include_directories(FileHandler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
