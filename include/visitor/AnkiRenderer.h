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
    None,
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

    static auto determine_cardType(Card& card) -> CardType;
    static auto is_cloze_card(Card const& card) -> bool;

    static std::map<std::string, FieldType> FieldKeywordMap;
    static auto determine_fieldType(Field const& field, std::map<std::string, FieldType> FieldKeywordMap) -> FieldType;
    static auto determine_keyword_in_heading(Heading const& heading, std::map<std::string, FieldType> keywordMap)
        -> FieldType;
    static auto field_contains_cloze(Field const& field) -> bool;
};

class AnkiRenderer
{
  public:
    AnkiRenderer() = default;
    AnkiRenderer(Document const& document);
    auto render(Document const& document) -> std::string;
    auto render_card(Card const& card) -> std::string;
    auto render_basic_card(Card const& card) -> std::string;
    auto render_cloze_card(Card const& card) -> std::string;

  private:
    std::string output;
};

class FieldRenderer : public Visitor
{
  public:
    auto render(Field const& field) -> std::string;
    auto get_output() const -> std::string;

    void visit(Paragraph const& node) override;
    void visit(Heading const& node) override;
    void visit(Text const& node) override;
    void visit(InlineMath const& node) override;

  private:
    std::string output;
};
