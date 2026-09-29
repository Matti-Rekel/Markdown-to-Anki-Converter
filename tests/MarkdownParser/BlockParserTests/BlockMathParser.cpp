#include <gtest/gtest.h>

#include "parser/Parser.h"

TEST(BlockMathParserTests, isBlockMath_detectsCodeBlock)
{
    const auto document = Parser::parse("$$ a^2 $$");

    ASSERT_EQ(document.children.size(), 1);

    const auto* heading = dynamic_cast<const BlockMath*>(document.children[0].get());

    ASSERT_NE(heading, nullptr);
}

/*
TEST(ParserTest, ParsesHeading)
{
    const auto document = Parser::parse("# Hello");

    ASSERT_EQ(document.children.size(), 1);

    const auto* heading = dynamic_cast<const Heading*>(document.children[0].get());

    ASSERT_NE(heading, nullptr);
    EXPECT_EQ(heading->level, 1);
}
TEST(ParserTest, ParsesParagraph)
{
    const auto document = Parser::parse("Hello world");

    ASSERT_EQ(document.children.size(), 1);

    const auto* paragraph = dynamic_cast<const Paragraph*>(document.children[0].get());

    ASSERT_NE(paragraph, nullptr);
}
*/
