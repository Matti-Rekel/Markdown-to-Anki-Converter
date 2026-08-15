#ifndef PARSER_H
#define PARSER_H

auto parser(std::string text) -> std::string;

auto parse_linebreak    (std::string & text) -> void;
auto parse_inlinemath   (std::string & text) -> void;
auto parse_inlinecode   (std::string & text) -> void;
auto parse_highlights   (std::string & text) -> void;
auto parse_cloze        (std::string & text) -> void;
auto parse_image        (std::string & text) -> void;
auto parse_link         (std::string & text) -> void;
auto parse_charakters   (std::string & text) -> void;

auto parse_codeblock    (std::string & text) -> void;
auto parse_mathblock    (std::string & text) -> void;
auto parse_list         (std::string & text) -> void;
auto parse_quote        (std::string & text) -> void;
auto parse_table        (std::string & text) -> void;

#endif
