add_executable(Converter main.cpp)

target_include_directories(Converter
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Converter
    FileHandler
    CardParser
)
