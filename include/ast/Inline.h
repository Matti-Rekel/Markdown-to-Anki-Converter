#pragma once

#include "Node.h"
#include <memory>
#include <string>
#include <vector>

// Extension: if you want a new Inline you need to change/add:
// - starts_inline
// - parse_inline
// - Add new class akin to InlineMathParser
// - include new class in CMake
// - create new visitor function

class Inline : public Node
{
  public:
    virtual ~Inline() = default;
};

class Text : public Inline
{
  public:
    std::string text;

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};

class InlineMath : public Inline
{
  public:
    std::string equation;

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};

class InlineCode : public Inline
{
  public:
    std::string code;

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};

class InlineStrong : public Inline
{
  public:
    std::vector<std::unique_ptr<Inline>> children;

    void accept(Visitor& visitor) const override { visitor.visit(*this); }
};
