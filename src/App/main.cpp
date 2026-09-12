#include <iostream>
#include <map>
#include <string>

#include "FileInput.h"
#include "ParseCards.h"
#include "parser/Parser.h"

int main()
{
    std::string filePath = "";
    filePath = "/home/Matti/Projekte/Markdown-to-Anki-Converter/Output/md_file.md";

    auto content = get_file_content(filePath);
    std::map<std::string, fields> keywords;
    keywords.insert({"### Hinweis:", fields::Hint});
    auto cards = parse_into_cards(content, keywords);
    Document res = Parser::parse({"# Überschrift $(a+b)^2 = a^2 +2ab + b^2$ und mehr Text"});

    for (const auto& block : res.children)
    {
        if (auto* heading = dynamic_cast<Heading*>(block.get()))
        {
            for (const auto& child : heading->children)
            {
                if (auto* text = dynamic_cast<Text*>(child.get()))
                {
                    std::cout << text->text << std::endl;
                }
            }
        }
    }
}
