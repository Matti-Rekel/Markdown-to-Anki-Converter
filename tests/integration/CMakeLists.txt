add_executable(ConverterIntegrationTests
ConverterIntegrationTests.cpp
)

target_link_libraries(ConverterIntegrationTests
    PRIVATE
        MarkdownParser
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(ConverterIntegrationTests)
