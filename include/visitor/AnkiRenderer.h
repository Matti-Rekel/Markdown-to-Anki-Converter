#pragma once

#include "Visitor.h"
#include "ast/Block.h"
#include "ast/Document.h"

#include <memory>
#include <string>
#include <vector>

enum class FieldType
{
    Question,
    Answer,
    Cloze
};
enum class CardType
{
    Basic,
    Cloze
};
class Field
{
  public:
    std::vector<Block const*> children;
    FieldType fieldType;
};

class Card
{
  public:
    std::vector<Field> fields;
    CardType cardType;
};

class CardParser
{
  public:
    static auto split_into_cards(Document const& node) -> std::vector<Card>;
    static auto consume_card(Document const& document, size_t& i) -> Card;
    static auto consume_field(Document const& document, size_t& i) -> Field;

    static auto determine_cardType(Card const& card) -> CardType;
    static auto is_cloze_card(Card const& card) -> bool;

    static auto determine_fieldType(Field const& field) -> FieldType;
};

class AnkiRenderer : public Visitor
{
  public:
    void render(Document const& document);
    auto render_card(Card const& card) -> std::string;

    void visit(Paragraph& node) override;
    void visit(Heading& node) override;
    void visit(Text& node) override;
    void visit(InlineMath& node) override;

    const std::string& getOutput() const;

  private:
    std::string output;
};
