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
    virtual void accept(Visitor& visitor) const = 0;
};

class Paragraph : public Block
{
  public:
    std::vector<std::unique_ptr<Inline>> children;

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};

class Heading : public Block
{
  public:
    Heading() { level = 0; };

    std::vector<std::unique_ptr<Inline>> children;
    unsigned int level;

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};
