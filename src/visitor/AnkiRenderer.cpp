#include "visitor/AnkiRenderer.h"

#include "ast/Block.h"
#include "ast/Document.h"
#include "ast/Inline.h"

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
