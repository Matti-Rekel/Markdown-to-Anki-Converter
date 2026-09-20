#pragma once

#include "Visitor.h"
#include "ast/Block.h"

#include <memory>
#include <string>
#include <vector>

enum class FieldType
{
    Question,
    Answer
};
enum class CardType
{
    Basic,
    Cloze
};
class Field
{
    auto determine_fieldType() -> FieldType;

    std::vector<std::unique_ptr<Block>> children;
    FieldType fieldType;
};

class Card
{
    auto determine_cardType() -> CardType;

    std::vector<Field> fields;
    CardType cardType;
};

class AnkiRenderer : public Visitor
{
  public:
    void render(Document& node);
    auto split_into_cards() -> std::vector<Card>;

    void visit(Paragraph& node) override;
    void visit(Heading& node) override;
    void visit(Text& node) override;
    void visit(InlineMath& node) override;

    const std::string& getOutput() const;

  private:
    std::string output;
};
