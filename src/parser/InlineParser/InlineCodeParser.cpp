#include "parser/InlineParser/InlineCodeParser.h"

auto InlineCodeParser::is_inlineCode(Cursor cursor) -> bool { return cursor.starts_with({"`"}); }

auto InlineCodeParser::parse(Cursor& cursor) -> std::unique_ptr<InlineCode>
{
    auto result = std::make_unique<InlineCode>();

    Range constructRange = determine_construct_range(cursor);
    Range contentRange = determine_content_range(cursor, constructRange);

    Cursor contentCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));

    result->code = parse_content(contentCursor);
    cursor.consume_range(constructRange.end - constructRange.start);

    return result;
}

auto InlineCodeParser::parse_content(Cursor& cursor) -> std::string { return std::string(cursor.get_content()); }

auto InlineCodeParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    // Skip opening delimiter.
    cursor.advance();

    while (!cursor.is_end_of())
    {
        if (cursor.starts_with("`"))
        {
            cursor.advance();

            result.end = cursor.get_position();
            return result;
        }

        cursor.advance();
    }

    // No closing delimiter found.
    result.end = cursor.get_position();

    return result;
}

auto InlineCodeParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;
    result.start = constructRange.start + 1;
    result.end = constructRange.end - 1;
    return result;
}
