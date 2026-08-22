#ifndef PARSECARDS_H
#define PARSECARDS_H

#include "Structures.h"

#include <string>
#include <vector>
#include <map>
#include <utility>



auto parse_into_cards(std::string const & document, std::map<std::string, fields> keywords) -> std::vector<Card>;


auto split_by_headings(const std::string& text) -> std::vector<std::string>;
auto split_text(std::string text, std::map<std::string, fields> keywords) -> Card;
auto find_question(std::string const& text, size_t& index) -> std::string;
auto find_answer(std::string const & text, size_t & index) -> std::string;
auto find_extra_fields(std::string text, size_t & index, std::map<std::string, fields>) -> std::map<fields, std::string>;
auto split_into_extra(std::string text, size_t index) -> std::vector<std::string>;
auto get_extra(std::string & text, std::vector<size_t> i) -> std::vector<std::string>;
auto find_keyword(std::string text, std::map<std::string, fields> keywords) -> std::pair<fields, std::string>;

#endif
