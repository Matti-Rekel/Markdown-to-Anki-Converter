#pragma once

#include "Node.h"
#include <string>

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
