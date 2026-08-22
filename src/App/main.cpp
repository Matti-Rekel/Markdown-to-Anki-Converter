#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include "FileInput.h"
#include "ParseCards.h"

int main(){
    std::string filePath = "";
    filePath = "/home/Matti/Projekte/Markdown-to-Anki-Converter/Output/md_file.md";

    auto content = get_file_content(filePath);
    std::map<std::string, fields> keywords;
    keywords.insert({"### Hinweis:", fields::Hint});
    auto cards = parse_into_cards(content, keywords);
    for (auto card : cards){
        std::cout << card.Answer << std::endl;
    }
}
