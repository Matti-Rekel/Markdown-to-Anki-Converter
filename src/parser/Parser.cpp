
#include "parser/Parser.h"
#include "parser/Cursor.h"

auto Parser::parse(std::string_view source) -> Document
{
    Document document;
    Cursor cursor{source};

    while (!cursor.is_end_of())
    {
        while (cursor.is_empty_line())
        {
            cursor.consume_line();
        }

        if (cursor.is_end_of())
            break;

        document.children.push_back(BlockParser::parse_block(cursor));
    }

    return document;
}
