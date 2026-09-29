#include "parser/BlockParser/BlockListParser.h"
#include "parser/InlineParser/InlineParser.h"

#include <cctype>
#include <cstddef>
#include <memory>

namespace
{
auto is_digit(char character) -> bool { return std::isdigit(static_cast<unsigned char>(character)) != 0; }
} // namespace

/*
 * The cursor is expected to point to the beginning of a line.
 *
 * This function also handles indentation, so it recognizes:
 *
 *     - item
 *
 * and:
 *
 *         - nested item
 */
auto BlockListParser::is_blockList(const Cursor& cursor) -> bool
{
    if (cursor.is_end_of() || cursor.is_empty_line())
    {
        return false;
    }

    Cursor markerCursor = cursor;
    markerCursor.consume_range(cursor.get_indentation());

    return is_unordered_list(markerCursor) || is_ordered_list(markerCursor);
}

auto BlockListParser::is_unordered_list(const Cursor& cursor) -> bool
{
    return cursor.starts_with("- ") || cursor.starts_with("* ") || cursor.starts_with("+ ");
}

auto BlockListParser::is_ordered_list(const Cursor& cursor) -> bool
{
    const auto position = cursor.get_position();
    const auto& content = cursor.get_content();

    if (position >= content.size())
    {
        return false;
    }

    std::size_t current = position;

    /*
     * An ordered-list marker must start with at least one digit.
     */
    if (!is_digit(content[current]))
    {
        return false;
    }

    while (current < content.size() && is_digit(content[current]))
    {
        ++current;
    }

    /*
     * There must be room for ". ".
     */
    if (current >= content.size() || content[current] != '.')
    {
        return false;
    }

    ++current;

    return current < content.size() && content[current] == ' ';
}

auto BlockListParser::parse(Cursor& cursor) -> std::unique_ptr<List>
{
    auto list = std::make_unique<List>();

    /*
     * The indentation of the first item defines the indentation
     * level of this list.
     */
    const std::size_t indentation = cursor.get_indentation();

    Cursor markerCursor = cursor;
    markerCursor.consume_range(indentation);

    if (!is_unordered_list(markerCursor) && !is_ordered_list(markerCursor))
    {
        /*
         * Ideally parse() should only be called after is_blockList().
         * How you handle this error depends on your parser design.
         */
        return list;
    }

    list->ordered = is_ordered_list(markerCursor);

    while (!cursor.is_end_of())
    {
        /*
         * In this implementation, a blank line terminates the list.
         */
        if (cursor.is_empty_line())
        {
            break;
        }

        const std::size_t currentIndentation = cursor.get_indentation();

        /*
         * A line with smaller indentation belongs to an outer block.
         */
        if (currentIndentation < indentation)
        {
            break;
        }

        /*
         * A more deeply indented line belongs to the previous list
         * item and is handled by parse_item().
         */
        if (currentIndentation > indentation)
        {
            break;
        }

        /*
         * Inspect the marker without modifying the real cursor.
         */
        Cursor currentMarker = cursor;
        currentMarker.consume_range(indentation);

        const bool validMarker = list->ordered ? is_ordered_list(currentMarker) : is_unordered_list(currentMarker);

        if (!validMarker)
        {
            break;
        }
        list->children.push_back(parse_item(cursor, indentation, list->ordered));
    }

    return list;
}

auto BlockListParser::parse_item(Cursor& cursor, std::size_t indentation, bool ordered) -> std::unique_ptr<ListItem>
{
    auto item = std::make_unique<ListItem>();

    /*
     * Move from the beginning of the line to the list marker.
     */
    cursor.consume_range(indentation);

    /*
     * Consume "- ", "* ", "+ ", or an ordered marker such as "1. ".
     */
    consume_marker(cursor, ordered);

    /*
     * Parse the text on the marker's line as a paragraph.
     *
     * Example:
     *
     *     - first item
     *
     * becomes:
     *
     *     ListItem
     *       Paragraph("first item")
     */
    item->children.push_back(parse_item_text(cursor));

    /*
     * parse_item_text() leaves the cursor at the beginning of the
     * following line.
     */
    while (!cursor.is_end_of())
    {
        if (cursor.is_empty_line())
        {
            break;
        }

        const std::size_t childIndentation = cursor.get_indentation();

        /*
         * A line with equal or smaller indentation does not belong
         * to this item.
         */
        if (childIndentation <= indentation)
        {
            break;
        }

        /*
         * Parse an indented list as a child of this ListItem.
         */
        if (has_nested_list(cursor, indentation))
        {
            item->children.push_back(parse(cursor));
            continue;
        }

        /*
         * Indented continuation paragraphs and other nested block
         * types are not handled yet.
         */
        break;
    }

    return item;
}

auto BlockListParser::consume_marker(Cursor& cursor, bool ordered) -> void
{
    if (!ordered)
    {
        /*
         * Consume "- ", "* ", or "+ ".
         */
        cursor.consume_range(2);
        return;
    }

    /*
     * Consume the numeric part of an ordered marker.
     */
    while (!cursor.is_end_of())
    {
        const std::size_t position = cursor.get_position();
        const auto& content = cursor.get_content();

        if (position >= content.size() || !is_digit(content[position]))
        {
            break;
        }

        cursor.consume_range(1);
    }

    /*
     * Consume ". ".
     *
     * parse_item() is only called after the marker has been
     * validated by is_ordered_list().
     */
    cursor.consume_range(2);
}

auto BlockListParser::parse_item_text(Cursor& cursor) -> std::unique_ptr<Paragraph>
{
    auto paragraph = std::make_unique<Paragraph>();

    const auto start = cursor.get_position();
    const auto& content = cursor.get_content();

    /*
     * Find the end of the current list-item line.
     */
    auto lineEnd = content.find('\n', start);

    if (lineEnd == std::string::npos)
    {
        lineEnd = content.size();
    }

    /*
     * Give InlineParser only the current line. This prevents it
     * from consuming nested items, sibling items, or later blocks.
     */
    const std::string line = std::string(content.substr(start, lineEnd - start));
    Cursor lineCursor(line);

    while (!lineCursor.is_end_of())
    {
        const auto previousPosition = lineCursor.get_position();

        paragraph->children.push_back(InlineParser::parse_inline(lineCursor));

        /*
         * Protect against a malformed inline parser that does not
         * advance its cursor.
         */
        if (lineCursor.get_position() == previousPosition)
        {
            lineCursor.consume_range(1);
        }
    }

    /*
     * Advance the real document cursor over the item text.
     */
    cursor.consume_range(lineEnd - start);

    /*
     * Consume the newline so that the cursor points to the
     * beginning of the next line.
     */
    if (lineEnd < content.size() && content[lineEnd] == '\n')
    {
        cursor.consume_range(1);
    }

    return paragraph;
}

auto BlockListParser::has_nested_list(const Cursor& cursor, std::size_t parentIndentation) -> bool
{
    if (cursor.is_end_of() || cursor.is_empty_line())
    {
        return false;
    }

    const std::size_t childIndentation = cursor.get_indentation();

    if (childIndentation <= parentIndentation)
    {
        return false;
    }

    /*
     * is_blockList() already removes indentation before examining
     * the marker.
     */
    return is_blockList(cursor);
}
