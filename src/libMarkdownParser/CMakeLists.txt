add_library(MarkdownParser
    Cursor.cpp

    parser/Parser.cpp

    parser/BlockParser/BlockParser.cpp
    parser/BlockParser/BlockHeadingParser.cpp
    parser/BlockParser/BlockParagraphParser.cpp

    parser/InlineParser/InlineParser.cpp
    parser/InlineParser/InlineMathParser.cpp
    parser/InlineParser/InlineTextParser.cpp
)

target_include_directories(MarkdownParser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
