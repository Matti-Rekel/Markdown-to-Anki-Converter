#include "BlockParser.h"
#include "Cursor.h"
#include "InlineParser.h"
#include "ast/Block.h"
#include <memory>

auto BlockParser::parse_block(Cursor& cursor) -> std::unique_ptr<Block>
{
    if (HeadingParser::starts_block(cursor))
        return HeadingParser::parse(cursor);

    return ParagraphParser::parse(cursor);
}

auto HeadingParser::parse(Cursor& cursor) -> std::unique_ptr<Heading>
{
    const auto range = determine_range(cursor);

    auto heading = std::make_unique<Heading>();

    while (cursor.get_position() != range.end)
    {
        heading->children.push_back(InlineParser::parse_inline(cursor, range));
    }

    return heading;
}

auto HeadingParser::determine_range(Cursor cursor) -> Range
{
    Range res;
    res.start = cursor.get_position();
    cursor.consume_line();
    res.end = cursor.get_position();
    return res;
}

auto HeadingParser::starts_block(Cursor cursor) -> bool { return cursor.starts_with({"#"}); }

auto ParagraphParser::parse(Cursor& cursor) -> std::unique_ptr<Paragraph>
{
    auto paragraph = std::make_unique<Paragraph>();

    // TODO: implement

    return paragraph;
}
