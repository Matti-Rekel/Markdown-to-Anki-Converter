#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>

// --- Structs and Enums ---

enum class BlockType {
    Paragraph,
    Code,
    Math,
    List,
};

struct Block {
    BlockType type;
    std::string content;
};



auto parser(std::string text) -> std::string;

// Block Parser 

auto parse_into_blocks  (std::string & text) -> std::vector<Block>;
auto parse_split_lines(std::string_view text) -> std::vector<std::string>;

auto begining_of_block(std::string line) -> BlockType;

auto parse_codeblock    (std::vector<std::string> lines, size_t & index) -> Block;
    auto begining_of_codeblock   (std::string line)   -> bool;
    auto end_of_codeblock        (std::string line)   -> bool;
auto parse_mathblock    (std::vector<std::string> lines, size_t & index) -> Block;
    auto begining_of_mathblock   (std::string line)   -> bool;
    auto end_of_mathblock        (std::string line)   -> bool;
auto parse_listblock    (std::vector<std::string> lines, size_t & index) -> Block;
    auto begining_of_listblock   (std::string line)   -> bool;
    auto end_of_listblock        (std::string line)   -> bool;

auto parse_paragraph(std::vector<std::string> lines, size_t& index) -> Block;


























enum class InlineType {
    Text,
    Strong,
    Emphasis,
    Code,
    Highlight,
    Math,
    Image,
    Link,
    LineBreak,
    Cloze
};

struct Inline {
    InlineType type;
    std::string content;
};


// Line Parser

auto parse_inlines(std::string_view text) -> std::vector<Inline>;

auto parse_linebreak    (std::string & text) -> void;
auto parse_inlinemath   (std::string & text) -> void;
auto parse_inlinecode   (std::string & text) -> void;
auto parse_highlights   (std::string & text) -> void;
auto parse_cloze        (std::string & text) -> void;
auto parse_image        (std::string & text) -> void;
auto parse_link         (std::string & text) -> void;
auto parse_charakters   (std::string & text) -> void;


#endif
