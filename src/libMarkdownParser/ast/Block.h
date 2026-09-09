#pragma once

#include "Inline.h"
#include "Node.h"
#include <memory>
#include <vector>

class Block : public Node
{
    virtual ~Block() = default;
};

class Paragraph : public Block
{
    std::vector<std::unique_ptr<Inline>> children;
};
