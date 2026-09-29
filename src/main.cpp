#include <iostream>
#include <string>

#include "io/AnkiWriter.h"
#include "io/FileInput.h"
#include "parser/Parser.h"
#include "visitor/AnkiRenderer.h"

int main()
{
    std::string filePath = "";
    std::cout << "Pleas enter the File Path\n";
    std::cin >> filePath;

    auto content = get_file_content(filePath);

    Document res = Parser::parse(content);
    AnkiRenderer renderer;
    std::string output = renderer.render(res);
    write_card_to_output(output);
}
