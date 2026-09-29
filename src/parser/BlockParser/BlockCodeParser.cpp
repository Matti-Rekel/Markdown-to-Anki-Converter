#include "parser/BlockParser/BlockCodeParser.h"
#include "ast/Inline.h"
#include "parser/Cursor.h"
#include <memory>

auto BlockCodeParser::is_blockCode(Cursor cursor) -> bool { return cursor.starts_with({"```"}); }

auto BlockCodeParser::parse(Cursor& cursor) -> std::unique_ptr<BlockCode>
{
    auto codeBlock = std::make_unique<BlockCode>();

    const auto constructRange = determine_construct_range(cursor);
    const auto contentRange = determine_content_range(cursor, constructRange);

    Cursor inlineCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));

    codeBlock->code = parse_content(inlineCursor);

    cursor.consume_range(constructRange.end - constructRange.start);

    return codeBlock;
}

auto BlockCodeParser::parse_content(Cursor& cursor) -> std::string { return std::string(cursor.get_content()); }

auto BlockCodeParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    cursor.consume_line();

    while (!cursor.is_end_of())
    {

        if (cursor.starts_with("```"))
        {
            cursor.consume_line();
            break;
        }
        cursor.consume_line();
    }

    result.end = cursor.get_position();
    return result;
}
auto BlockCodeParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;
    cursor.consume_line();
    result.start = cursor.get_position();

    while (!cursor.is_end_of())
    {

        if (cursor.starts_with("```"))
        {
            break;
        }
        cursor.consume_line();
    }

    result.end = cursor.get_position();

    return result;
}
