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
