#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "FileHandler.h"
#include "Formatter.h"
#include "Parser.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;


int main(){
    string filePath = "";
    cout << "Please paste file path for a file you want converted to Anki cards: ";
    //cin >> filePath;
    filePath = "/home/Matti/Projekte/Markdown-to-Anki-Converter/Output/md_file.md";



    auto v = get_Card_starts(filePath);
    auto s = read_Card(v.at(0), v.at(1), filePath);
    //cout << s << endl;


    std::map<std::string, fields> keywords;
    keywords.insert({"### Hinweis:", fields::Hint});
    Card first = split_text(s, keywords);
    cout << "Frage: " << first.Question;
    cout << "Antwort: " << first.Answer;
    cout << "Hinweis: " << first.Hint;

}
