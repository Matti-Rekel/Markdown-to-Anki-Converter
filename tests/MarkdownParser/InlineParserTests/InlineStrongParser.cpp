#include "parser/InlineParser/InlineStrongParser.h"
#include <gtest/gtest.h>

#include "parser/InlineParser/InlineParser.h"

TEST(InlineParserStrongTest, IsInlineStrong_detectsStrong)
{
    Cursor cursor("**a^2**");

    ASSERT_EQ(InlineStrongParser::is_inlineStrong(cursor), true);
}
