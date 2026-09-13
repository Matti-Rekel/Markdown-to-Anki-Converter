
#include <gtest/gtest.h>

#include "parser/Parser.h"

TEST(ParserTest, EmptyDocument)
{
    const auto document = Parser::parse("");

    EXPECT_TRUE(document.children.empty());
}
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
