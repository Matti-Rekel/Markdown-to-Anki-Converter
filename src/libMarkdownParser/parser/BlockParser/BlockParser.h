#pragma once

#include "Cursor.h"
#include "ast/Block.h"
#include <memory>

class BlockParser
{
  public:
    static auto starts_block(Cursor& cursor) -> bool;
    static auto parse_block(Cursor& cursor) -> std::unique_ptr<Block>;
};

class ParagraphParser
{
  public:
    static auto parse(Cursor& cursor) -> std::unique_ptr<Paragraph>;

  private:
    static auto determine_range(Cursor cursor) -> Range;
};
