#pragma once

#include <string_view>

class Cursor
{
  public:
    explicit Cursor(std::string_view content_);

    auto get_position() const -> size_t;
    auto get_size() const -> size_t;
    auto is_end_of() const -> bool;

    auto advance(std::size_t count = 1) -> void;

    auto peek_line() const -> std::string_view;
    auto consume_line() -> std::string_view;

    auto peek_range(size_t range) const -> std::string_view;
    auto starts_with(std::string_view text) const -> bool;
    auto consume_range(size_t range) -> std::string_view;

  private:
    std::string_view content;
    size_t pos = 0;
    size_t size;
};
