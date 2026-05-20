#include <iostream>
#include <string>
#include "FileHandler.h"

using std::cout;
using std::cin;
using std::string;

int main(){
    string filePath = "";
    cout << "Please paste file path for a file you want converted to Anki cards: ";
    cin >> filePath;
    test();
}
