#include "BlockParser.h"
#include "../InlineParser/InlineParser.h"
#include "BlockHeadingParser.h"
#include "BlockParagraphParser.h"
#include "Cursor.h"
#include "ast/Block.h"
#include <memory>

auto BlockParser::parse_block(Cursor& cursor) -> std::unique_ptr<Block>
{
    if (HeadingParser::is_blockHeading(cursor))
        return HeadingParser::parse(cursor);

    return ParagraphParser::parse(cursor);
}

auto BlockParser::starts_block(Cursor cursor) -> bool { return HeadingParser::is_blockHeading(cursor); }
