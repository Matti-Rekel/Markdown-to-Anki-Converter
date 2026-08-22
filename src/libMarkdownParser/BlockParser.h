#ifndef BLOCK_PARSER_H
#define BLOCK_PARSER_H

#include <string>
#include <vector>
#include <memory>
#include <variant>

#include "Inline_Parser.h"

struct Paragraph {
    std::vector<Inline> children;
};

struct Heading {
    int level;
    std::vector<Inline> children;
};

struct CodeBlock {
    std::string language;
    std::string code;
};

struct MathBlock{
    std::string expresion;
}

using Block = std::variant<
    Paragraph,
    Heading,
    CodeBlock,
    MathBlock,
>;

class BlockParser{
public:
    auto parse_to_Blocks(std::string const & text) -> std::vector<Block>;

private:
    auto parse_Paragraph(std::string const & text) -> Block;
    auto parse_Heading(std::string const & text) -> Block;
    auto parse_CodeBlock(std::string const & text) -> Block;
    auto parse_MathBlock(std::string const & text) -> Block;
};

#endif
