#pragma once

#include "Visitor.h"

#include <string>

class AnkiRenderer : public Visitor
{
  public:
    void render(Document& node);
    void visit(Paragraph& node) override;
    void visit(Heading& node) override;
    void visit(Text& node) override;
    void visit(InlineMath& node) override;

    const std::string& getOutput() const;

  private:
    std::string output;
};
