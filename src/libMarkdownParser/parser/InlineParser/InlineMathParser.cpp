#include "InlineMathParser.h"

auto InlineMathParser::is_inlineMath(Cursor cursor) -> bool { return cursor.starts_with({"$"}); }

auto InlineMathParser::parse(Cursor& cursor) -> std::unique_ptr<InlineMath>
{
    auto result = std::make_unique<InlineMath>();

    Range constructRange = determine_construct_range(cursor);
    Range contentRange = determine_content_range(cursor, constructRange);

    Cursor contentCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));

    result->equation = parse_content(contentCursor);
    cursor.consume_range(constructRange.end - constructRange.start);

    return result;
}

auto InlineMathParser::parse_content(Cursor& cursor) -> std::string { return std::string(cursor.get_content()); }

auto InlineMathParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    // Skip opening delimiter.
    cursor.advance();

    while (!cursor.is_end_of())
    {
        if (cursor.starts_with("$"))
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

auto InlineMathParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;
    result.start = constructRange.start + 1;
    result.end = constructRange.end - 1;
    return result;
}
