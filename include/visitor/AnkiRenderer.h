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
  public:
    static auto determine_fieldType(Field const& field) -> FieldType;

    std::vector<Block const*> children;
    FieldType fieldType;
};

class Card
{
  public:
    static auto determine_cardType(Card const& card) -> CardType;

    std::vector<Field> fields;
    CardType cardType;
};

class AnkiRenderer : public Visitor
{
  public:
    void render(Document const& document);
    auto split_into_cards(Document const& node) -> std::vector<Card>;
    auto render_card(Card const& card) -> std::string;

    void visit(Paragraph& node) override;
    void visit(Heading& node) override;
    void visit(Text& node) override;
    void visit(InlineMath& node) override;

    const std::string& getOutput() const;

  private:
    std::string output;
};
