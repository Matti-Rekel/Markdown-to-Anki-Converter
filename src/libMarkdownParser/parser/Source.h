#pragma once

#include <cstddef>
#include <string_view>

class Source
{
  public:
    explicit Source(std::string_view input) : input_(input) {}

    [[nodiscard]]
    bool eof() const
    {
        return position_ >= input_.size();
    }

    [[nodiscard]]
    std::string_view currentLine() const;

    void consumeLine();

    [[nodiscard]]
    std::string_view remaining() const
    {
        return input_.substr(position_);
    }

  private:
    std::string_view input_;
    std::size_t position_ = 0;
};
