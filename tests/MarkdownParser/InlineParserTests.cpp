
#include <gtest/gtest.h>

#include "parser/InlineParser/InlineParser.h"

TEST(InlineParserTest, DetectsInlineMath)
{
    Cursor cursor("$a^2$");
    const auto content = InlineParser::parse_inline(cursor);

    const auto* inlineMath = dynamic_cast<const InlineMath*>(content.get());

    ASSERT_NE(inlineMath, nullptr);
    EXPECT_EQ(inlineMath->equation, "a^2");
}
