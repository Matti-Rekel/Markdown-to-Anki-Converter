#include "Parser.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

auto split_text(string text, std::map<string, fields> keywords) -> Card {
    Card res;


    size_t index = 1;
    res.Question = find_question(text, index);
    res.Answer = find_answer(text, index);
    std::map<fields, string> extraFields = find_extra_fields(text, index, keywords);

    for (fields a : {
        fields::Question,
        fields::Prerequisites,
        fields::Hint,
        fields::Answer,
        fields::Add_Information,
        fields::Source}){
        auto it = extraFields.find(a);
        if (it != extraFields.end()){
            switch (a){
                case fields::Prerequisites :
                    res.Prerequisites = extraFields.at(fields::Prerequisites);
                    break;
                case fields::Hint :
                    res.Hint = extraFields.at(fields::Hint);
                    break;
                case fields::Add_Information :
                    res.Add_Information = extraFields.at(fields::Add_Information);
                    break;
                case fields::Source :
                    res.Source = extraFields.at(fields::Source);
                    break;
            }
        }
    }
    /* Der Plan:
     * Die Überschrift mit ## ist die Frage. Direkt gefolgt von der Antwort.
     * Die Zusatzfelder werden danach mit ### Makiert.
     * In keywords ist Gespeichert, welche Wörter hinter ### welchem Feld zuzuordnen sind.
    */

    return res;
}

auto find_question(string text, size_t & index) -> string{
    string res = "";
    auto two_linebreaks = [](string text, size_t index) -> bool {return text.at(index-1) == '\n' && text.at(index) == '\n';};
    while (index < text.length() && !two_linebreaks(text, index)) {
        res.push_back(text.at(index));
        index++;
    }
    return res;
}

auto find_answer(string text, size_t & index) -> string{
    string res = "";
    auto card_close_done = [](size_t length, size_t index) -> bool {return length - index < 5;};
    auto extra_field_starting = [&text](size_t index) -> bool{return (index < text.length()-4 && !(text.at(index - 1) == '\n' && text.at(index) == '#' && text.at(index+1) == '#' && text.at(index+2) == '#' && text.at(index+3) == ' ')); };
    while(card_close_done(text.length(), index) || extra_field_starting(index)){
        res.push_back(text.at(index));
        index++;
    }
    return res;
}

auto find_extra_fields(string text, size_t & index, std::map<string, fields> keywords) -> std::map<fields, string>{
    std::map<fields, string> res;
    vector<string> extra = split_into_extra(text, index);
    for (auto a : extra){
        auto b = find_keyword(a, keywords);
        res.insert({b.first, b.second});
    }
return res;
}

auto split_into_extra(string text, size_t index) -> std::vector<string>{
    std::vector<size_t> i;
    while(index < text.length()){
        if ((index+3 < text.length()) &&(text.at(index-1) == '\n' && text.at(index) == '#' && text.at(index+1) == '#' && text.at(index+2) == '#' && text.at(index+3) == ' ')) {
            i.push_back(index);
        }
        index++;
    }
    i.push_back(text.length());
    return get_extra(text, i);
}

auto get_extra(string & text, vector<size_t> i) -> std::vector<string>{
    vector<string> res;
    size_t index = i.at(0);
    for (size_t j = 1; j < i.size(); j++) {
        string s = "";
        while(index < i.at(j)){
            s.push_back(text.at(index));
            index++;
        }
        res.push_back(s);
        index++;
    }
    return res;
}

auto find_keyword(string text, std::map<string, fields> keywords) -> std::pair<fields, string> {
    std::pair<fields, string> res;
    std::string keyword = "";
    std::string txt = "";
    size_t index = 0;
    while(index < text.length() && text.at(index) != '\n'){
        keyword.push_back(text.at(index));
        index++;
    }
    while(index < text.length()){
        txt.push_back(text.at(index));
        index++;
    }
    auto it = keywords.find(keyword);
    if (it != keywords.end()){
        res= std::pair<fields, string> {keywords.at(keyword), txt};
    }
    else cout << "Invalid Card marker";
    return res;
}

