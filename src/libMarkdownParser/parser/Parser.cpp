
#include "Parser.h"
#include "BlockParser.h"

auto Parser::parse(std::string_view source) -> Document
{
    Document document;
    while (!endOfSource)
    {
        skip_blank_lines();

        document.children.push_back(BlockParser::parse_block());
    }
}
