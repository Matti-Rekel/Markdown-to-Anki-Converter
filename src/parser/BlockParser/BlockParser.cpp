#include "parser/BlockParser/BlockParser.h"
#include "ast/Block.h"
#include "parser/BlockParser/BlockClozeParser.h"
#include "parser/BlockParser/BlockCodeParser.h"
#include "parser/BlockParser/BlockHeadingParser.h"
#include "parser/BlockParser/BlockListParser.h"
#include "parser/BlockParser/BlockMathParser.h"
#include "parser/BlockParser/BlockParagraphParser.h"
#include "parser/Cursor.h"
#include "parser/InlineParser/InlineParser.h"
#include <memory>

auto BlockParser::parse_block(Cursor& cursor) -> std::unique_ptr<Block>
{
    if (HeadingParser::is_blockHeading(cursor))
        return HeadingParser::parse(cursor);
    if (BlockCodeParser::is_blockCode(cursor))
        return BlockCodeParser::parse(cursor);
    if (BlockMathParser::is_blockMath(cursor))
        return BlockMathParser::parse(cursor);
    if (BlockClozeParser::is_blockCloze(cursor))
        return BlockClozeParser::parse(cursor);
    if (BlockListParser::is_blockList(cursor))
        return BlockListParser::parse(cursor);

    return ParagraphParser::parse(cursor);
}

auto BlockParser::starts_block(Cursor cursor) -> bool
{
    return HeadingParser::is_blockHeading(cursor) || BlockCodeParser::is_blockCode(cursor) ||
           BlockMathParser::is_blockMath(cursor) || BlockClozeParser::is_blockCloze(cursor) ||
           BlockListParser::is_blockList(cursor);
}
