#ifndef PARSER_H
#define PARSER_H

#include<string>
#include<vector>


enum class BlockType {
    Paragraph,
    Heading,
    Code,
    Math,
    List,
    Quote,
    Table,
    ThematicBreak
};

struct Block {
    BlockType type;
    std::string content;
};


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


auto parser(std::string text) -> std::string;

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

// Block Parser 

auto parse_into_blocks  (std::string & text) -> std::vector<Block>;
auto parse_split_lines(std::string_view text) -> std::vector<std::string>;

auto parse_codeblock    (std::vector<std::string> lines, size_t & index) -> Block;
    auto is_beginingof_code(std::string line)   -> bool;
    auto is_endof_code(std::string line)        -> bool;
auto parse_mathblock    (std::string & text) -> void;
auto parse_list         (std::string & text) -> void;
auto parse_quote        (std::string & text) -> void;
auto parse_table        (std::string & text) -> void;




#endif
