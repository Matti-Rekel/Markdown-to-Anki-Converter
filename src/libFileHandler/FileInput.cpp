#include "FileInput.h"

#include <fstream>
#include <iostream>
#include <string>

auto get_file_content(const std::string& filePath) -> std::string {
    std::ifstream file(filePath);

    if (!file) {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return {};
    }

    return {
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    };
}
