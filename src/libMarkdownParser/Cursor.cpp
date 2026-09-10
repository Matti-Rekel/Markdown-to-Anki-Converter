#include "Cursor.h"

Cursor::Cursor(std::string_view content_) : content(content_) { size = content_.size(); }

auto Cursor::get_position() const -> size_t { return pos; }
auto Cursor::change_position_to(size_t pos_) -> void { pos = pos_; };
auto Cursor::get_size() const -> size_t { return size; }
auto Cursor::is_end_of() const -> bool { return pos >= size; }

auto Cursor::advance(std::size_t count) -> void
{
    pos += count;

    if (pos > content.size())
        pos = content.size();
}

auto Cursor::consume_line() -> std::string_view
{
    const auto old_pos = pos;
    const auto new_line = content.find('\n', pos);

    if (new_line == std::string_view::npos)
    {
        pos = content.size();
        return content.substr(old_pos);
    }

    pos = new_line + 1;

    return content.substr(old_pos, new_line - old_pos);
}
auto Cursor::peek_line() const -> std::string_view
{
    const auto pos_new_line = content.find('\n', pos);

    if (pos_new_line == std::string_view::npos)
        return content.substr(pos);

    return content.substr(pos, pos_new_line - pos);
}

auto Cursor::peek_range(std::size_t range) const -> std::string_view { return content.substr(pos, range); }
auto Cursor::starts_with(std::string_view text) const -> bool { return peek_range(text.size()) == text; }
auto Cursor::consume_range(size_t range) -> std::string_view
{
    const auto result = content.substr(pos, range);
    pos += result.size();

    return result;
}
