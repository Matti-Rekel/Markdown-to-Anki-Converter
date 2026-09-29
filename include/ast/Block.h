#pragma once

#include "Inline.h"
#include "Node.h"
#include <memory>
#include <string>
#include <vector>

// Extension: if you want a new Block you need to change/add:
// - parse_block
// - starts_block
// - Add new class akin to Heading
// - include new class in Cmake
// - create new visitor function

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

class BlockCode : public Block
{
  public:
    std::string code;

    // TODO: add support to detect language

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};

class BlockMath : public Block
{
  public:
    std::string equation;

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};
