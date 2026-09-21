#include "visitor/AnkiRenderer.h"

#include "ast/Block.h"
#include "ast/Document.h"
#include "ast/Inline.h"
#include <vector>

auto CardParser::determine_fieldType(const Field& field) -> FieldType
{
    // TODO
    return {};
}
auto CardParser::determine_cardType(const Card& card) -> CardType
{
    for (auto field : card.fields)
    {
        field.fieldType = CardParser::determine_fieldType(field);
    }
    // TODO

    if (is_cloze_card(card))
        return CardType::Cloze;

    return CardType::Basic;
}
auto is_cloze_card(Card const& card) -> bool { return card.fields.at(2).fieldType == FieldType::Cloze; }

void AnkiRenderer::render(Document const& node)
{
    auto cards = CardParser::split_into_cards(node);

    for (auto& card : cards)
    {
        card.cardType = CardParser::determine_cardType(card);

        output += render_card(card);
    }
}

auto CardParser::split_into_cards(Document const& document) -> std::vector<Card>
{
    std::vector<Card> result;

    for (std::size_t i = 0; i < document.children.size(); ++i)
    {
        auto* cardHeading = dynamic_cast<Heading const*>(document.children[i].get());

        if (cardHeading && cardHeading->level == 2)
            result.push_back(consume_card(document, i));
    }

    return result;
}

auto AnkiRenderer::consume_card(Document const& document, std::size_t& i) -> Card
{
    Card result;

    // The ## heading starts the question field.
    Field field;
    field.children.push_back(document.children.at(i).get());
    result.fields.push_back(std::move(field));

    ++i;

    while (i < document.children.size())
    {
        // TODO currently the Answer will be part of the question field
        auto* heading = dynamic_cast<Heading const*>(document.children[i].get());

        // We reached the beginning of the next card.
        if (heading && heading->level == 2)
        {
            --i;
            break;
        }

        // We reached the beginning of a new field.
        if (heading && heading->level == 3)
        {
            Field newField;
            newField.children.push_back(document.children[i].get());
            result.fields.push_back(std::move(newField));
        }
        else
        {
            // Add the node to the current field.
            result.fields.back().children.push_back(document.children[i].get());
        }

        ++i;
    }

    return result;
}

auto AnkiRenderer::render_card(Card const& card) -> std::string
{
    // TODO
    return {};
}
void AnkiRenderer::visit(Paragraph& node)
{
    // TODO
}

void AnkiRenderer::visit(Heading& node)
{
    // TODO
}

void AnkiRenderer::visit(Text& node)
{
    // TODO
}

void AnkiRenderer::visit(InlineMath& node)
{
    // TODO
}
