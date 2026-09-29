#include "parser/InlineParser/InlineEmphasisParser.h"
#include <gtest/gtest.h>

TEST(InlineParserStrongTest, IsInlineEmphasis_detectsStrong)
{
    Cursor cursor("*a^2*");

    ASSERT_EQ(InlineEmphasisParser::is_inlineEmphasis(cursor), true);
}
