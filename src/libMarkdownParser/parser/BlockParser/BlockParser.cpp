#include "BlockParser.h"
#include "../InlineParser/InlineParser.h"
#include "BlockHeadingParser.h"
#include "Cursor.h"
#include "ast/Block.h"
#include <memory>

auto BlockParser::parse_block(Cursor& cursor) -> std::unique_ptr<Block>
{
    if (HeadingParser::starts_block(cursor))
        return HeadingParser::parse(cursor);

    return ParagraphParser::parse(cursor);
}

auto ParagraphParser::parse(Cursor& cursor) -> std::unique_ptr<Paragraph>
{
    auto paragraph = std::make_unique<Paragraph>();

    // TODO: implement

    return paragraph;
}
