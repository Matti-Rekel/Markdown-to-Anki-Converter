#pragma once

#include "Inline.h"
#include "Node.h"

class Block : public Node
{
};

class Paragraph : public Block
{
    std::vector<std::unique_ptr<Inline>> children;
};
