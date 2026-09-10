add_library(MarkdownParser
    Cursor.cpp

    parser/Parser.cpp
    parser/BlockParser.cpp
    parser/InlineParser.cpp
)

target_include_directories(MarkdownParser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
