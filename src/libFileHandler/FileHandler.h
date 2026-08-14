#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <iostream>
#include <fstream>
#include <vector>


auto isValidPath(std::string path) -> bool;
auto isNewCard(size_t index, std::vector<char> c) -> bool;
auto isCardAtBegining(size_t index, std::vector<char> c) -> bool;

auto get_Card_starts (std::string filePath) -> std::vector<std::ios::pos_type>;
auto read_Card(std::ios::pos_type begining, std::ios::pos_type end, std::string filePath) -> std::string;

auto write_preamble(std::string path) -> void;
auto write_card_to_file(std::string path) -> void;



void test();

#endif
