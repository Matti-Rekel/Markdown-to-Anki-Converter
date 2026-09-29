#pragma once

class Document;
class Paragraph;
class Heading;
class BlockCode;
class BlockMath;
class BlockCloze;
class ListItem;
class List;

class Text;
class InlineMath;
class InlineCode;
class InlineStrong;
class InlineEmphasis;
class InlineCloze;

class Visitor
{
  public:
    virtual ~Visitor() = default;

    virtual void visit(Paragraph const& node) = 0;
    virtual void visit(Heading const& node) = 0;
    virtual void visit(BlockCode const& node) = 0;
    virtual void visit(BlockMath const& node) = 0;
    virtual void visit(BlockCloze const& node) = 0;
    virtual void visit(ListItem const& node) = 0;
    virtual void visit(List const& node) = 0;

    virtual void visit(Text const& node) = 0;
    virtual void visit(InlineMath const& node) = 0;
    virtual void visit(InlineCode const& node) = 0;
    virtual void visit(InlineStrong const& node) = 0;
    virtual void visit(InlineEmphasis const& node) = 0;
    virtual void visit(InlineCloze const& node) = 0;
};
