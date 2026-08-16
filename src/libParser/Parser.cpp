#include "Parser.h"

auto parse_into_blocks(std::string_view text) -> std::vector<Block>{
    std::vector<Block> res;
    std::vector<std::string> lines = parse_split_lines(text);

    bool paragraph = false;
    size_t index = 0;
    while (index < lines.length()){

        if (is_beginingof_code(lines.at(index))) {
            res.push_back(parse_codeblock(lines, index));
            continue;
        }
    }


    return {};
}

auto parse_split_lines(std::string_view text) -> std::vector<std::string>{
    std::vector<std::string> res;
    size_t index = 0;
    while (index < text.length()) {
        std::string line = "";
        while (index < text.length() && text.at(index) != '\n') {
            line.push_back(text.at(index));
            index++;
        }
        res.push_back(line);
        index++;
    }
    return res;
}

auto parse_codeblock(std::vector<std::string> lines, size_t & index) -> Block{
    Block result;
    result.type = BlockType::Code;

    // Skip first line
    index++;

    while(index < lines.size()){

        if(is_endof_code(lines.at(index))){
            index++;
            break;
        }

        if (!result.content.empty())
            result.content += '\n';

        result.content += lines[index];

        ++index;
    }
    return result;
}
auto is_beginingof_code(std::string line) -> bool{
    if (line.size() > 2 && (line.at(0) == '`' && line.at(1) == '`' && line.at(2) == '`')) {
        return true;
    }
    return false;
}
auto is_endof_code(std::string line) -> bool{
    if (line.size() > 2 && (line.at(0) == '`' && line.at(1) == '`' && line.at(2) == '`')) {
        return true;
    }
    return false;
}

auto parse_mathblock(std::vector<std::string> lines, size_t & index) -> Block{
    Block result;
    result.type = BlockType::Math;

    index++;

    while(index < lines.size()){
        if(is_endof_math(lines.at(index))){
            index++;
            break;
        }


    }
}
