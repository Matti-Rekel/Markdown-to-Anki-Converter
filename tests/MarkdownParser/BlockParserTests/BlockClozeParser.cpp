#include <gtest/gtest.h>

#include "parser/BlockParser/BlockClozeParser.h"
#include "parser/Parser.h"

TEST(BlockClozeParserTests, isBlockCloze_detects)
{
    const auto document = Parser::parse("___Test___");

    ASSERT_EQ(document.children.size(), 1);

    const auto* cloze = dynamic_cast<const BlockCloze*>(document.children[0].get());

    ASSERT_NE(cloze, nullptr);
}

TEST(BlockClozeParserTests, isBlockCloze_detectsMultLines)
{
    std::string text = "___\n"
                       "$f, f_1, f_2, ...$ nichtnegativ messbar, so dass $f_1 \\leq f_2 \\leq f_3 \\leq ... $\n"
                       "$\\mu$-f.ü. und $\\lim f_n = f$ $\\mu$-f.ü.\n"
                       "___";

    const auto document = Parser::parse(text);

    ASSERT_EQ(document.children.size(), 1);

    const auto* cloze = dynamic_cast<const BlockCloze*>(document.children[0].get());

    ASSERT_NE(cloze, nullptr);
}

TEST(BlockClozeParserTests, isBlockCloze_detectsMathBlock)
{
    std::string text = "___\n$$a$$\n___";
    Cursor cursor{text};

    bool isCloze = BlockClozeParser::is_blockCloze(cursor);

    ASSERT_TRUE(isCloze);

    Range constructRange = BlockClozeParser::determine_construct_range(cursor);
    ASSERT_EQ(constructRange.start, 0);
    ASSERT_EQ(constructRange.end, 13);

    Cursor inlineCursor{"\n$$a$$\n"};

    /*
        const auto document = Parser::parse(text);

        ASSERT_EQ(document.children.size(), 1);

        const auto* cloze = dynamic_cast<const BlockCloze*>(document.children[0].get());

        ASSERT_NE(cloze, nullptr);
    */
}