#include "BlockHeadingParser.h"

auto HeadingParser::is_blockHeading(Cursor cursor) -> bool { return cursor.starts_with({"#"}); }

auto HeadingParser::parse(Cursor& cursor) -> std::unique_ptr<Heading>
{
    auto heading = std::make_unique<Heading>();

    const auto constructRange = determine_construct_range(cursor);

    Cursor inlineCursor(cursor.consume_range(range.end - range.start));

    while (inlineCursor.get_position() != range.end)
    {
        heading->children.push_back(InlineParser::parse_inline(inlineCursor));
    }

    return heading;
}

auto HeadingParser::parse_content(const Cursor& cursor) -> std::vector<std::unique_ptr<Inline>> {}

auto HeadingParser::determine_heading_level(const Cursor& cursor) -> unsigned int {}

auto HeadingParser::determine_construct_range(Cursor cursor) -> Range {}
auto HeadingParser::determine_content_range(Cursor cursor, Range constructRange) -> Range {}
