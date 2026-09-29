#pragma once

#include "BlockParser.h"
#include "parser/InlineParser/InlineParser.h"

class BlockClozeParser
{
  public:
    static auto is_blockCloze(Cursor cursor) -> bool;
    static auto parse(Cursor& cursor) -> std::unique_ptr<BlockCloze>;
    static auto parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Block>>;

  private:
    static auto determine_construct_range(Cursor cursor) -> Range;
    static auto determine_content_range(Cursor cursor, Range constructRange) -> Range;
};
