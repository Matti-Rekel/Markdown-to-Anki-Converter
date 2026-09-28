#pragma once

#include "InlineParser.h"
#include "parser/Cursor.h"

class InlineMathParser
{
  public:
    static auto is_inlineMath(Cursor cursor) -> bool;
    static auto parse(Cursor& cursor) -> std::unique_ptr<InlineMath>;
    static auto parse_content(Cursor& cursor) -> std::string;

  private:
    static auto determine_construct_range(Cursor cursor) -> Range;
    static auto determine_content_range(Cursor cursor, Range constructRange) -> Range;
};
