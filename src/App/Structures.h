#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<string>

struct Card {
    std::string Question         = "";
    std::string Answer           = "";
    std::string Prerequisites    = "";
    std::string Hint             = "";
    std::string Add_Information  = "";
    std::string Source           = "";
};
enum class fields{
    Question, Prerequisites, Hint, Answer, Add_Information, Source
};

#endif
