#pragma once

#include "Block.h"
#include <memory>
#include <vector>

class Document
{
  public:
    std::vector<std::unique_ptr<Block>> children;
};
