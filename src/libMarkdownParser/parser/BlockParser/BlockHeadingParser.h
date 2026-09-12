#pragma once

#include "../InlineParser/InlineParser.h"
#include "BlockParser.h"

class HeadingParser
{
  public:
    static auto is_blockHeading(Cursor cursor) -> bool;
    static auto parse(Cursor& cursor) -> std::unique_ptr<Heading>;
    static auto parse_content(const Cursor& cursor) -> std::vector<std::unique_ptr<Inline>>;

    static auto determine_heading_level(const Cursor& cursor) -> unsigned int;

  private:
    static auto determine_construct_range(Cursor cursor) -> Range;
    static auto determine_content_range(Cursor cursor, Range constructRange) -> Range;
};
