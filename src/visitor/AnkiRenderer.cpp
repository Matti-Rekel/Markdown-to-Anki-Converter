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

    if (is_cloze_card(card))
        return CardType::Cloze;

    return CardType::Basic;
}
auto CardParser::is_cloze_card(Card const& card) -> bool { return card.fields.at(2).fieldType == FieldType::Cloze; }

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

    std::size_t i = 0;

    while (i < document.children.size())
    {
        auto* cardHeading = dynamic_cast<Heading const*>(document.children[i].get());

        if (cardHeading && cardHeading->level == 2)
        {
            result.push_back(consume_card(document, i));
        }
        else
        {
            ++i;
        }
    }

    return result;
}

auto CardParser::consume_card(Document const& document, std::size_t& i) -> Card
{
    Card result;

    // ## Question starts the card and belongs to its own field.
    Field question;
    question.children.push_back(document.children.at(i).get());
    result.fields.push_back(std::move(question));

    ++i;

    while (i < document.children.size())
    {
        auto* heading = dynamic_cast<Heading const*>(document.children.at(i).get());

        // The next ## heading starts the next card.
        if (heading && heading->level == 2)
            break;

        result.fields.push_back(consume_field(document, i));
    }

    return result;
}

auto CardParser::consume_field(Document const& document, std::size_t& i) -> Field
{
    Field result;

    // A ### heading starts a field and belongs to that field.
    if (i < document.children.size())
    {
        auto* heading = dynamic_cast<Heading const*>(document.children.at(i).get());

        if (heading && heading->level == 3)
        {
            result.children.push_back(document.children.at(i).get());
            ++i;
        }
    }

    // Consume everything until the next heading.
    while (i < document.children.size())
    {
        auto* heading = dynamic_cast<Heading const*>(document.children.at(i).get());

        if (heading && (heading->level == 2 || heading->level == 3))
            break;

        result.children.push_back(document.children.at(i).get());
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
