#include <gtest/gtest.h>

#include "parser/Parser.h"

TEST(BlockParserTests, parseBlock_emptyline)
{
    std::string text = {"\n$$a$$\n"};
    Cursor cursor{text};

    const auto* math = dynamic_cast<const BlockMath*>(BlockParser::parse_block(cursor).get());

    ASSERT_NE(math, nullptr);
}
