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
};
