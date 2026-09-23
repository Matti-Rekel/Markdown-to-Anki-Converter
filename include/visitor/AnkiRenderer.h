#pragma once

#include "Visitor.h"
#include "ast/Block.h"
#include "ast/Document.h"

#include <map>
#include <string>
#include <vector>

// Extension: If you want a new fieldType to be supported you need to add/change:
// - enum class FieldType
// - determine_fieldType
// - FieldKeywordMap (There is currently one in CardParser and another one in determine_cardType)
enum class FieldType
{
    Question,
    Answer,
    Cloze
};

// Extension: If you want a new CardType to be supported you need to add/change:
// - enum class CardType
// - determine_cardType
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

    static std::map<std::string, FieldType> FieldKeywordMap;
    static auto determine_fieldType(Field const& field, std::map<std::string, FieldType> FieldKeywordMap) -> FieldType;
    static auto determine_keyword_in_heading(Heading const& heading, std::map<std::string, FieldType> keywordMap)
        -> FieldType;
    static auto field_contains_cloze(Field const& field) -> bool;
};

class AnkiRenderer : public Visitor
{
  public:
    AnkiRenderer() = delete;
    AnkiRenderer(Document const& document);
    void render(Document const& document);
    auto render_card(Card const& card) -> std::string;
    auto render_basic_card(Card const& card) -> std::string;
    auto render_cloze_card(Card const& card) -> std::string;

    void visit(Paragraph& node) override;
    void visit(Heading& node) override;
    void visit(Text& node) override;
    void visit(InlineMath& node) override;

    const std::string& getOutput() const;

  private:
    std::string output;
};
