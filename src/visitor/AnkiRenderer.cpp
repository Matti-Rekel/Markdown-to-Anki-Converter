#include "visitor/AnkiRenderer.h"

#include "ast/Block.h"
#include "ast/Document.h"
#include "ast/Inline.h"
#include <vector>

auto Field::determine_fieldType(const Field& field) -> FieldType
{
    // TODO
    return {};
}
auto Card::determine_cardType(const Card& card) -> CardType
{
    // TODO
    return {};
}

void AnkiRenderer::render(Document const& node)
{
    auto cards = split_into_cards(node);

    for (auto& card : cards)
    {
        card.cardType = Card::determine_cardType(card);

        output += render_card(card);
    }
}

auto AnkiRenderer::split_into_cards(Document const& document) -> std::vector<Card>
{
    std::vector<Card> result;

    for (std::size_t i = 0; i < document.children.size(); ++i)
    {
        Card card;

        auto* cardHeading = dynamic_cast<Heading const*>(document.children[i].get());

        if (cardHeading && cardHeading->level == 2)
        {
            Field question;
            question.children.push_back(document.children[i].get());
            card.fields.push_back(std::move(question));

            ++i;

            while (i < document.children.size())
            {
                auto* heading = dynamic_cast<Heading const*>(document.children[i].get());

                if (heading && heading->level == 2)
                {
                    --i;
                    break;
                }

                if (heading && heading->level == 3)
                {
                    Field field;
                    field.children.push_back(document.children[i].get());
                    card.fields.push_back(std::move(field));
                }
                else
                {
                    card.fields.back().children.push_back(document.children[i].get());
                }

                ++i;
            }

            result.push_back(std::move(card));
        }
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
