#pragma once

#include "BlockParser.h"
#include "parser/InlineParser/InlineParser.h"

class HeadingParser
{
  public:
    static auto is_blockHeading(Cursor cursor) -> bool;
    static auto parse(Cursor& cursor) -> std::unique_ptr<Heading>;
    static auto parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Inline>>;

    static auto determine_heading_level(Cursor cursor) -> unsigned int;

  private:
    static auto determine_construct_range(Cursor cursor) -> Range;
    static auto determine_content_range(Cursor cursor, Range constructRange) -> Range;
};
