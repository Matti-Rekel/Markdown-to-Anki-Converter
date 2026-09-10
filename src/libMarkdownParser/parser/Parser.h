#pragma once

#include "BlockParser.h"
#include "ast/Document.h"
#include <string_view>

class Parser
{
  public:
    static auto parse(std::string_view source) -> Document;
};
