#pragma once

#include "visitor/Visitor.h"

class Node
{
  public:
    virtual ~Node() = default;

    virtual void accept(Visitor& visitor) = 0;
};
