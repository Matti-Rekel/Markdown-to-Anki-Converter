add_executable(VisitorTests
    AnkiRendererTests.cpp
)

target_include_directories(VisitorTests
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(VisitorTests
    PRIVATE
        MarkdownParser
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(VisitorTests)
