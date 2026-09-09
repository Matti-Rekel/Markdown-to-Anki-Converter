#include "Source.h"

std::string_view Source::currentLine() const
{
    auto remaining = input_.substr(position_);

    auto newline = remaining.find('\n');

    if (newline == std::string_view::npos)
        return remaining;

    return remaining.substr(0, newline);
}

void Source::consumeLine()
{
    auto newline = input_.find('\n', position_);

    if (newline == std::string_view::npos)
    {
        position_ = input_.size();
        return;
    }

    position_ = newline + 1;
}
