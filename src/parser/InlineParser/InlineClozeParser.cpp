#include "parser/InlineParser/InlineClozeParser.h"
#include "parser/InlineParser/InlineParser.h"

auto InlineClozeParser::is_inlineCloze(Cursor cursor) -> bool { return cursor.starts_with({"__"}); }

auto InlineClozeParser::parse(Cursor& cursor) -> std::unique_ptr<InlineCloze>
{
    auto result = std::make_unique<InlineCloze>();

    Range constructRange = determine_construct_range(cursor);
    Range contentRange = determine_content_range(cursor, constructRange);

    Cursor contentCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));

    result->children = parse_content(contentCursor);
    cursor.consume_range(constructRange.end - constructRange.start);

    return result;
}

auto InlineClozeParser::parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Inline>>
{
    std::vector<std::unique_ptr<Inline>> result;
    while (!cursor.is_end_of())
    {
        result.push_back(InlineParser::parse_inline(cursor));
    }
    return result;
}

auto InlineClozeParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    // Skip opening delimiter.
    cursor.advance(2);

    while (!cursor.is_end_of())
    {
        if (cursor.starts_with("__"))
        {
            cursor.advance(2);

            result.end = cursor.get_position();
            return result;
        }

        cursor.advance();
    }

    // No closing delimiter found.
    result.end = cursor.get_position();

    return result;
}

auto InlineClozeParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;
    result.start = constructRange.start + 2;
    result.end = constructRange.end - 2;
    return result;
}
