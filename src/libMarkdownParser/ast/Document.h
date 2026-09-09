#pragma once

#include "Block.h"
#include <memory>
#include <vector>

class Document
{
    std::vector<std::unique_ptr<Block>> Nodes;
};
