#include "AnkiRenderer.h"

#include "../libMarkdownParser/ast/Block.h"
#include "../libMarkdownParser/ast/Document.h"
#include "../libMarkdownParser/ast/Inline.h"

void AnkiRenderer::render(Document& node)
{
    for (auto& child : node.children)
    {
        child->accept(*this);
    }
}

void AnkiRenderer::visit(Paragraph& node)
{
    for (auto& child : node.children)
    {
        child->accept(*this);
    }

    output += "\n";
}

void AnkiRenderer::visit(Heading& node)
{
    for (auto& child : node.children)
    {
        child->accept(*this);
    }

    output += "\n";
}

void AnkiRenderer::visit(Text& node) { output += node.text; }

void AnkiRenderer::visit(InlineMath& node)
{
    output += "$";
    output += node.equation;
    output += "$";
}

const std::string& AnkiRenderer::getOutput() const { return output; }
