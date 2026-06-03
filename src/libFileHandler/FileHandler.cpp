#include "FileHandler.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool isValidPath(string Path){
    fstream MyFile(Path);
    return !MyFile;
}

void readFile(string Path){
    std::ifstream file(Path);

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::string line;
    std::vector<std::string> card{};

    while (std::getline(file, line)) {
        card.push_back(line);
    }
    std::cout << card.at(0) << "\n";

    file.close();
}

