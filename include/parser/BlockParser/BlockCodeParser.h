#pragma once

#include "BlockParser.h"
#include "parser/InlineParser/InlineParser.h"

class BlockCodeParser
{
  public:
    static auto is_blockCode(Cursor cursor) -> bool;
    static auto parse(Cursor& cursor) -> std::unique_ptr<BlockCode>;
    static auto parse_content(Cursor& cursor) -> std::string;

  private:
    static auto determine_construct_range(Cursor cursor) -> Range;
    static auto determine_content_range(Cursor cursor, Range constructRange) -> Range;
};
