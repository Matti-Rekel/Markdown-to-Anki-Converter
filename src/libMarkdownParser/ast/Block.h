#pragma once

#include "Inline.h"
#include "Node.h"
#include <memory>
#include <string>
#include <vector>

class Block : public Node
{
  public:
    virtual ~Block() override = default;
};

class Paragraph : public Block
{
  public:
    std::vector<std::unique_ptr<Inline>> children;

    void accept(Visitor& visitor) override;
};

class Heading : public Block
{
  public:
    std::vector<std::unique_ptr<Inline>> children;
    unsigned int level;

    void accept(Visitor& visitor) override;
};
