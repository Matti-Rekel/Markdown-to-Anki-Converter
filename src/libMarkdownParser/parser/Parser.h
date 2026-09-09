#pragma once

#include "BlockParser.h"
#include "Document.h"
#include <string_view>

class Parser
{
  public:
    Document parse(std::string_view source);
};
