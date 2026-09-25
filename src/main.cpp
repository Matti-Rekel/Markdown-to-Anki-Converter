#include <iostream>
#include <string>

#include "io/FileInput.h"
#include "parser/Parser.h"
#include "visitor/AnkiRenderer.h"

int main()
{
    std::string filePath = "";
    filePath = "/home/Matti/Projekte/Markdown-to-Anki-Converter/Output/md_file.md";

    auto content = get_file_content(filePath);

    std::string text;
    text = "## Überschrift" + '\n';
    text += "Text";

    Document res = Parser::parse(text);
    AnkiRenderer renderer;
    std::string output = renderer.render(res);
    std::cout << output << std::endl;
}
