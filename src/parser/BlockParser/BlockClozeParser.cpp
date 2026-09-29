#include "parser/BlockParser/BlockClozeParser.h"
#include "parser/Cursor.h"
#include <memory>

auto BlockClozeParser::is_blockCloze(Cursor cursor) -> bool { return cursor.starts_with({"___"}); }

auto BlockClozeParser::parse(Cursor& cursor) -> std::unique_ptr<BlockCloze>
{
    auto result = std::make_unique<BlockCloze>();

    const auto constructRange = determine_construct_range(cursor);
    const auto contentRange = determine_content_range(cursor, constructRange);

    Cursor inlineCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));

    result->children = parse_content(inlineCursor);

    cursor.consume_range(constructRange.end - constructRange.start);

    return result;
}

auto BlockClozeParser::parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Block>>
{

    std::vector<std::unique_ptr<Block>> result;
    while (!cursor.is_end_of())
    {
        result.push_back(BlockParser::parse_block(cursor));
    }
    return result;
}

auto BlockClozeParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    // Skip opening delimiter.
    cursor.advance(3);

    while (!cursor.is_end_of())
    {
        if (cursor.starts_with("___"))
        {
            cursor.advance(3);

            result.end = cursor.get_position();
            return result;
        }

        cursor.advance();
    }

    // No closing delimiter found.
    result.end = cursor.get_position();

    return result;
}

auto BlockClozeParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;

    result.start = constructRange.start + 3;
    result.end = constructRange.end - 3;

    if (result.start < result.end && cursor.at(result.start) == '\n')
    {
        ++result.start;
    }

    return result;
}
