#include "parser/BlockParser/BlockParagraphParser.h"
#include "parser/BlockParser/BlockParser.h"
#include "parser/InlineParser/InlineParser.h"

// TODO:
// - If there is a completly empty line between a new Paragraph should be created and the empty line should be part of
// none.

auto ParagraphParser::parse(Cursor& cursor) -> std::unique_ptr<Paragraph>
{
    auto paragraph = std::make_unique<Paragraph>();

    Range constructRange = determine_construct_range(cursor);
    const auto contentRange = determine_content_range(cursor, constructRange);

    Cursor inlineCursor(cursor.get_content().substr(contentRange.start, contentRange.end - contentRange.start));
    paragraph->children = parse_content(inlineCursor);

    cursor.consume_range(constructRange.end - constructRange.start);

    return paragraph;
}

auto ParagraphParser::parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Inline>>
{
    std::vector<std::unique_ptr<Inline>> result;
    while (!cursor.is_end_of())
    {
        result.push_back(InlineParser::parse_inline(cursor));
    }
    return result;
}

auto ParagraphParser::determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    while (!cursor.is_end_of())
    {
        if (BlockParser::starts_block(cursor))
            break;

        if (cursor.is_empty_line())
            break;

        cursor.consume_line();
    }

    result.end = cursor.get_position();

    return result;
}

auto ParagraphParser::determine_content_range(Cursor cursor, Range constructRange) -> Range
{
    Range result;
    result.start = constructRange.start;

    if (cursor.at(result.end - 1) == '\n')
    {
        result.end = constructRange.end - 1;
    }
    else
    {
        result.end = constructRange.end;
    }

    return result;
}
