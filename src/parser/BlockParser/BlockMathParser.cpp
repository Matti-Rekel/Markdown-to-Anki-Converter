#include "parser/BlockParser/BlockMathParser.h"
#include "parser/Cursor.h"
#include <iostream>
#include <memory>

auto BlockMathParser::is_blockMath(Cursor cursor) -> bool { return cursor.starts_with({"$$"}); }

auto BlockMathParser::parse(Cursor& cursor) -> std::unique_ptr<BlockMath>
{
    auto mathBlock = std::make_unique<BlockMath>();

    const auto constructRange = determine_construct_range(cursor);
    const auto contentRange = determine_content_range(cursor, constructRange);

    Cursor inlineCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));

    mathBlock->equation = parse_content(inlineCursor);

    cursor.consume_range(constructRange.end - constructRange.start);

    return mathBlock;
}

auto BlockMathParser::parse_content(Cursor& cursor) -> std::string { return std::string(cursor.get_content()); }

auto BlockMathParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    cursor.advance(2);

    while (!cursor.is_end_of())
    {

        if (cursor.starts_with("$$"))
        {
            cursor.advance(2);
            break;
        }
        cursor.advance();
    }

    result.end = cursor.get_position();
    return result;
}
auto BlockMathParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;
    cursor.advance(2);
    result.start = cursor.get_position();

    while (!cursor.is_end_of())
    {

        if (cursor.starts_with("$$"))
        {
            break;
        }
        cursor.advance();
    }

    result.end = cursor.get_position();

    return result;
}
