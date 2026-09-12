#pragma once

#include "Cursor.h"
#include "ast/Inline.h"
#include <memory>

class InlineParser
{
  public:
    static auto parse_inline(Cursor& cursor) -> std::unique_ptr<Inline>;
    static auto starts_inline(Cursor cursor) -> bool;
};

class TextParser
{
  public:
    static auto parse(Cursor& cursor) -> std::unique_ptr<Text>;
};
