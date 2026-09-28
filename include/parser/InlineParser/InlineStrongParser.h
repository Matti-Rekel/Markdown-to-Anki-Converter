#pragma once

#include "InlineParser.h"
#include "parser/Cursor.h"

class InlineStrongParser
{
  public:
    static auto is_inlineStrong(Cursor cursor) -> bool;
    static auto parse(Cursor& cursor) -> std::unique_ptr<InlineStrong>;
    static auto parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Inline>>;

  private:
    static auto determine_construct_range(Cursor cursor) -> Range;
    static auto determine_content_range(Cursor cursor, Range constructRange) -> Range;
};
