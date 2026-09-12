#include "BlockParagraphParser.h"
#include "BlockParser.h"

auto ParagraphParser::parse(Cursor& cursor) -> std::unique_ptr<Paragraph>
{
    auto paragraph = std::make_unique<Paragraph>();

    Range constructRange = determine_construct_range(cursor);

    Cursor inlineCursor(cursor.get_content().substr(constructRange.start, constructRange.end - constructRange.start));
    paragraph->children = parse_content(inlineCursor);

    cursor.consume_range(constructRange.end - constructRange.start);

    return paragraph;
}

auto parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Inline>> {}

auto determine_construct_range(Cursor cursor) -> Range
{
    Range result;
    result.start = cursor.get_position();

    while (!BlockParser::starts_block(cursor))
    {
        cursor.consume_line();
    }
    result.end = cursor.get_position();
    return result;
}
