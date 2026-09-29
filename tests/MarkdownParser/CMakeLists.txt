add_executable(MarkdownParserTests
    CursorTests.cpp
    ParserTests.cpp
    BlockParserTests.cpp
    InlineParserTests.cpp

    BlockParserTests/BlockCodeParser.cpp

    InlineParserTests/InlineStrongParser.cpp
    InlineParserTests/InlineEmphasisParser.cpp


)

target_link_libraries(MarkdownParserTests
    PRIVATE
        MarkdownParser
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(MarkdownParserTests)
