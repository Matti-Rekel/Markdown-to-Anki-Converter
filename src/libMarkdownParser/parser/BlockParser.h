#pragma once

#include <memory>
#include <string_view>

class BlockParser
{
  public:
    static auto parse_block() -> std::unique_ptr<Block>;
    static auto is_start_of_new_Block(std::string_view source) -> bool;
};

class CodeBlockParser : public BlockParser
{
};
