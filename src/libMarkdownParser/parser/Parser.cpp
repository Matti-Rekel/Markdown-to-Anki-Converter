
#include "Parser.h"
#include "BlockParser.h"

auto Parser::parse(std::string_view source) -> Document
{
    Document document;

    Cursor cursor{source};

    while (!cursor.is_end_of())
    {

        if (cursor.is_end_of())
            break;

        document.children.push_back(BlockParser::parse_block(cursor));
    }

    return document;
}
