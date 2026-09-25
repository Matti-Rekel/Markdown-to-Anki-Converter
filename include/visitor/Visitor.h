#pragma once

class Document;
class Paragraph;
class Heading;
class Text;
class InlineMath;

class Visitor
{
  public:
    virtual ~Visitor() = default;

    virtual void visit(Paragraph const& node) = 0;
    virtual void visit(Heading const& node) = 0;

    virtual void visit(Text const& node) = 0;
    virtual void visit(InlineMath const& node) = 0;
};
