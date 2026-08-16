#include "Parser.h"

auto parser(std::string text) -> std::string{
std::vector<Block> blocks = parse_into_blocks(text);
for(auto block : blocks){
std::cout << block.content << std::endl;
}
std::vector<Inline> parts = parse_inlines(blocks.at(0).content);
for(auto part : parts){
std::cout << part.content << std::endl;
}

return {};
}

auto parse_into_blocks(std::string & text) -> std::vector<Block>{
std::vector<Block> res;
std::vector<std::string> lines = parse_split_lines(text);

size_t index = 0;
while (index < lines.size()){

BlockType blocktype = begining_of_block(lines.at(index));

switch (blocktype){
    case BlockType::Code :
        res.push_back(parse_codeblock(lines, index));
        break;
    case BlockType::Math :
        res.push_back(parse_mathblock(lines, index));
        break;
    case BlockType::List :
        res.push_back(parse_listblock(lines, index));
        break;
    default :
        res.push_back(parse_paragraph(lines, index));
        break;
}
}


return res;
}

auto parse_split_lines(std::string text) -> std::vector<std::string>{
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

// --- Parsing individual Blocks ---

auto parse_codeblock(std::vector<std::string> lines, size_t & index) -> Block{
Block result;
result.type = BlockType::Code;

index++;

while(index < lines.size()){

if(end_of_codeblock(lines.at(index))){
    index++;
    break;
}

if (!result.content.empty())
    result.content += '\n';

result.content += lines[index];

index++;
}
return result;
}


auto parse_mathblock(std::vector<std::string> lines, size_t & index) -> Block{
Block result;
result.type = BlockType::Math;

index++;

while(index < lines.size()){
if(end_of_mathblock(lines.at(index))){
    index++;
    break;
}

result.content += lines[index];

index++;
}
return result;
}


auto parse_listblock(std::vector<std::string> lines, size_t & index) -> Block{
Block result;
result.type = BlockType::List;

while(index < lines.size()){
if(end_of_listblock(lines.at(index))){
    index++;
    break;
}

result.content += lines[index] + '\n';

index++;
}
return result;
}

auto parse_paragraph(std::vector<std::string> lines, size_t& index) -> Block {
Block result;
result.type = BlockType::Paragraph;

while (index < lines.size() &&
    begining_of_block(lines.at(index)) == BlockType::Paragraph) {

if (!result.content.empty())
    result.content += '\n';

result.content += lines.at(index);
index++;
}

return result;
}

// --- Checking for Begining of Blocks ---

auto begining_of_block(std::string line) -> BlockType{
if(begining_of_codeblock(line)){
return BlockType::Code;
}
if(begining_of_mathblock(line)){
return BlockType::Math;
}
if(begining_of_listblock(line)){
return BlockType::List;
}
else{
return BlockType::Paragraph;
}
}


auto begining_of_codeblock(std::string line) -> bool{
if (line.size() > 2 && (line.at(0) == '`' && line.at(1) == '`' && line.at(2) == '`')) {
return true;
}
return false;
}

auto begining_of_mathblock(std::string line) -> bool{
if (line.size() > 1 && (line.at(0) == '$' && line.at(1) == '$')){
return true;
}
return false;
}

auto begining_of_listblock(std::string line) -> bool{
if(line.size() > 1 && (line.at(0) == '-' && line.at(1) == ' ')){
return true;
}
return false;
}

// --- Checking for End of Blocks ---

auto end_of_codeblock(std::string line) -> bool{
if (line.size() > 2 && (line.at(0) == '`' && line.at(1) == '`' && line.at(2) == '`')) {
return true;
}
return false;
}

auto end_of_mathblock(std::string line) -> bool{
if (line.size() > 1 && (line.at(0) == '$' && line.at(1) == '$')){
return true;
}
return false;
}

auto end_of_listblock(std::string line) -> bool{
if (line.empty()){
return true;
}
return false;
}


/*
--- Inline ---
*/

auto parse_inlines(std::string text) -> std::vector<Inline>{
std::vector<Inline> res;
size_t index = 0;
while (index < text.length()){

InlineType inlinetype = begining_of_inline(text, index);

switch (inlinetype){
    case InlineType::Math :
        res.push_back(parse_mathinline(text, index));
        break;
    case InlineType::Code :
        res.push_back(parse_codeinline(text, index));
        break;
    default :
        res.push_back(parse_text(text,index));
}

}
return res;
}

/*
--- Inline Parser ---
*/

auto parse_codeinline(std::string & text, size_t & index) -> Inline{
Inline res;
res.type = InlineType::Code;

index++;

while (index < text.length()){
    if (end_of_codeinline(text, index)) {
        index++;
        break;
    }

    res.content += text.at(index);
    index++;
}
return res;
}

auto parse_mathinline(std::string & text, size_t & index) -> Inline{
Inline res;
res.type = InlineType::Math;

index++;

while(index < text.length()){
    if (end_of_mathinline(text, index)) {
        index++;
        break;
    }

    res.content += text.at(index);
    index++;
}
return res;
}

auto parse_text(std::string & text, size_t & index) -> Inline{
Inline res;
res.type = InlineType::Text;

while (index < text.length() && begining_of_inline(text, index) == InlineType::Text){
    res.content += text.at(index);
    index++;
}
return res;
}

/*
--- Finding begining of Inline ---
*/

auto begining_of_inline(std::string text, size_t index) -> InlineType{
if (begining_of_codeinline(text, index)){
return InlineType::Code;
}
if (begining_of_mathinline(text, index)) {
return InlineType::Math;
}
return InlineType::Text;
}

auto begining_of_codeinline(std::string & text, size_t index) -> bool{
if (index < text.length() && text.at(index) == '`') {
    return true;
}
return false;
}
auto begining_of_mathinline(std::string & text, size_t index) -> bool{
if (index < text.length() && text.at(index) == '$'){
    return true;
}
return false;
}

/*
--- Finding end of Inline ---
*/

auto end_of_codeinline(std::string & text, size_t index) -> bool{
if (index < text.length() && text.at(index) == '`') {
    return true;
}
return false;
}

auto end_of_mathinline(std::string & text, size_t & index) -> bool{
if (index < text.length() && text.at(index) == '$'){
    return true;
}
return false;
}
