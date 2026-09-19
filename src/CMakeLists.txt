add_library(MarkdownParser
    io/FileInput.cpp
    io/AnkiWriter.cpp

    visitor/AnkiRenderer.cpp
    visitor/Visitor.cpp

    parser/Cursor.cpp
    parser/Parser.cpp

    parser/BlockParser/BlockParser.cpp
    parser/BlockParser/BlockHeadingParser.cpp
    parser/BlockParser/BlockParagraphParser.cpp

    parser/InlineParser/InlineParser.cpp
    parser/InlineParser/InlineMathParser.cpp
    parser/InlineParser/InlineTextParser.cpp
)

target_include_directories(MarkdownParser PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(Converter
    main.cpp
)

target_link_libraries(Converter PRIVATE
    MarkdownParser
)
