#ifndef FORMATTER_H
#define FORMATTER_H

#include <map>
#include <string>
#include <vector>
#include <utility>
    using std::string;

    struct Card {
        string Question         = "";
        string Answer           = "";
        string Prerequisites    = "";
        string Hint             = "";
        string Add_Information  = "";
        string Source           = "";
    };
    enum class fields{
        Question, Prerequisites, Hint, Answer, Add_Information, Source
    };


    auto split_text(std::string text, std::map<string, fields> keywords) -> Card;
    auto find_question(std::string text, size_t & index) -> std::string;
    auto find_answer(std::string text, size_t & index) -> std::string;
    auto find_extra_fields(string text, size_t & index, std::map<string, fields>) -> std::map<fields, string>;
    auto split_into_extra(string text, size_t index) -> std::vector<string>;
    auto get_extra(string & text, std::vector<size_t> i) -> std::vector<string>;
    auto find_keyword(string text, std::map<string, fields> keywords) -> std::pair<fields, string>;


    auto parse_md_to_html(string field) -> string;


#endif 
