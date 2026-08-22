add_library(CardParser ParseCards.cpp)

target_include_directories(CardParser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../App
)
