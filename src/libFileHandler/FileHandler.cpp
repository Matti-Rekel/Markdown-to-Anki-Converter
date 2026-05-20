#include "FileHandler.h"

#include <iostream>
#include <fstream>
using namespace std;

void test(){
    fstream MyFile("/home/Matti/Projekte/Markdown-to-Anki-Converter/Output/file.txt", ios::in | ios::out | ios::trunc);
    if (!MyFile) {
        cout << "failed\n";
        return;
    }
    MyFile << "Files can be tricky, but it is fun enough!";
    MyFile.seekg(0);
    string myText;
    getline(MyFile, myText);
    cout << myText;
}
