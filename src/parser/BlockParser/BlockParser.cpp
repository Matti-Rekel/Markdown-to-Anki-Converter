#include "parser/BlockParser/BlockParser.h"
#include "ast/Block.h"
#include "parser/BlockParser/BlockHeadingParser.h"
#include "parser/BlockParser/BlockParagraphParser.h"
#include "parser/Cursor.h"
#include "parser/InlineParser/InlineParser.h"
#include <memory>

auto BlockParser::parse_block(Cursor& cursor) -> std::unique_ptr<Block>
{
    if (HeadingParser::is_blockHeading(cursor))
        return HeadingParser::parse(cursor);

    return ParagraphParser::parse(cursor);
}

auto BlockParser::starts_block(Cursor cursor) -> bool { return HeadingParser::is_blockHeading(cursor); }
