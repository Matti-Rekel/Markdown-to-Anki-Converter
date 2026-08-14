#include "FileHandler.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool isValidPath(string Path){
    fstream MyFile(Path);
    return !MyFile;
}

bool isNewCard(size_t index, std::vector<char> c){
    return index >= 3 && c.at(index-3)== '\n' && c.at(index-2) == '#' && c.at(index-1) == '#' && c.at(index) == ' ';
}
bool isCardAtBegining(size_t index, std::vector<char> c){
    return index == 2 && c.at(index-2) == '#' && c.at(index-1) == '#' && c.at(index) == ' ';
}

std::vector<std::ios::pos_type> get_Card_starts(string filePath){
    std::ifstream input_file (filePath);
    std::vector<char> c;
    std::vector<std::ios::pos_type> positions;
    std::ios::pos_type pos;
    char a = ' ';
    size_t index = 0;
    while (input_file.get(a)){
        c.push_back(a);
        if (isNewCard(index, c) || isCardAtBegining(index, c)) {
            positions.push_back(input_file.tellg()- std::streamoff{3});
        }
        index++;
    }
    positions.push_back(input_file.tellg());
    input_file.close();
    return positions;
}

string read_Card(std::ios::pos_type begining, std::ios::pos_type end, string filePath){
    std::ifstream input_file (filePath);
    input_file.seekg(begining);
    string res;
    char c;
    while(input_file.get(c) && begining != end){
        res.push_back(c);
        begining += std::streamoff{1};
    }
    return res;
}

auto write_preamble(std::string path) -> void {
    std::ofstream out_put
}
