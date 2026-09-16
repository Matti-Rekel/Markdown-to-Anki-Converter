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

    virtual void visit(Document& node) = 0;

    virtual void visit(Paragraph& node) = 0;
    virtual void visit(Heading& node) = 0;

    virtual void visit(Text& node) = 0;
    virtual void visit(InlineMath& node) = 0;
};
