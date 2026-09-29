#ifndef BLOCK_LIST_PARSER_H
#define BLOCK_LIST_PARSER_H

#include "ast/Block.h"
#include "parser/Cursor.h"

#include <cstddef>
#include <memory>

class BlockListParser
{
  public:
    static auto is_blockList(const Cursor& cursor) -> bool;

    static auto parse(Cursor& cursor) -> std::unique_ptr<List>;

  private:
    static auto is_unordered_list(const Cursor& cursor) -> bool;
    static auto is_ordered_list(const Cursor& cursor) -> bool;

    static auto parse_item(Cursor& cursor, std::size_t indentation, bool ordered) -> std::unique_ptr<ListItem>;

    static auto consume_marker(Cursor& cursor, bool ordered) -> void;

    static auto parse_item_text(Cursor& cursor) -> std::unique_ptr<Paragraph>;

    static auto has_nested_list(const Cursor& cursor, std::size_t parentIndentation) -> bool;
};

#endif
