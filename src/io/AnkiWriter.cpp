#include "io/AnkiWriter.h"
#include <fstream>
#include <iostream>

auto write_card_to_output(std::string const& cards) -> void
{
    std::ofstream file("Output/Output.txt");

    if (!file)
        throw std::runtime_error("Could not open Output/Output.txt");

    file << "#separator:;\n";
    file << "#html:true\n";
    file << "#deck column:1\n";
    file << "#notetype column:2\n";
    file << "#tags column:3\n";
    file << "#guid column:4\n";
    file << "\n";

    file << cards;
}
