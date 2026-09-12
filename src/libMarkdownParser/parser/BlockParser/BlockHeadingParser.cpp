#include "BlockHeadingParser.h"
#include "../../Cursor.h"
#include "ast/Inline.h"
#include <memory>

auto HeadingParser::is_blockHeading(Cursor cursor) -> bool { return cursor.starts_with({"#"}); }

auto HeadingParser::parse(Cursor& cursor) -> std::unique_ptr<Heading>
{
    auto heading = std::make_unique<Heading>();

    const auto constructRange = determine_construct_range(cursor);
    const auto contentRange = determine_content_range(cursor, constructRange);

    Cursor inlineCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));

    heading->children = HeadingParser::parse_content(inlineCursor);
    heading->level = HeadingParser::determine_heading_level(cursor);

    cursor.consume_range(constructRange.end - constructRange.start);

    return heading;
}

auto HeadingParser::parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Inline>>
{
    std::vector<std::unique_ptr<Inline>> result;
    while (!cursor.is_end_of())
    {
        result.push_back(InlineParser::parse_inline(cursor));
    }
    return result;
}

auto HeadingParser::determine_heading_level(Cursor cursor) -> unsigned int
{
    unsigned int level = 0;
    while (cursor.peek_range(1) == "#")
    {
        cursor.advance();
        level += 1;
    }
    return level;
}

auto HeadingParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    cursor.consume_line();
    result.end = cursor.get_position();
    return result;
}
auto HeadingParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;
    while (cursor.peek_range(1) == "#" || cursor.peek_range(1) == " ")
    {
        cursor.advance();
    }
    result.start = cursor.get_position();
    result.end = constructRange.end;
    return result;
}
