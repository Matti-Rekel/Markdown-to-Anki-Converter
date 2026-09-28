#pragma once

class Document;
class Paragraph;
class Heading;
class Text;
class InlineMath;
class InlineCode;
class InlineStrong;

class Visitor
{
  public:
    virtual ~Visitor() = default;

    virtual void visit(Paragraph const& node) = 0;
    virtual void visit(Heading const& node) = 0;

    virtual void visit(Text const& node) = 0;
    virtual void visit(InlineMath const& node) = 0;
    virtual void visit(InlineCode const& node) = 0;
    virtual void visit(InlineStrong const& node) = 0;
};
