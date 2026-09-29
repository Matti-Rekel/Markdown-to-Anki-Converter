#include "visitor/AnkiRenderer.h"

#include "ast/Block.h"
#include "ast/Document.h"
#include "ast/Inline.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

auto CardParser::determine_fieldType(const Field& field, std::map<std::string, FieldType> keywordMap) -> FieldType
{
    if (field.children.size() > 0)
    {
        auto* heading = dynamic_cast<Heading const*>(field.children.at(0));
        if (heading)
        {
            if (heading->level == 2)
            {
                return FieldType::Question;
            }
            if (heading->level == 3)
            {
                return determine_keyword_in_heading(*heading, keywordMap);
            }
        }
        else if (field_contains_cloze(field))
        {
            return FieldType::Cloze;
        }
    }
    return FieldType::Answer;
}

auto CardParser::determine_keyword_in_heading(Heading const& heading, std::map<std::string, FieldType> keywordMap)
    -> FieldType
{
    if (!heading.children.empty())
    {

        auto text = dynamic_cast<Text*>(heading.children.at(0).get());
        if (text)
        {

            auto fieldType = keywordMap.find(text->text);

            if (fieldType != keywordMap.end())
            {
                return fieldType->second;
            }
            else
            {
                return FieldType::Extra;
            }
        }
    }
    return FieldType::Answer;
}

auto CardParser::field_contains_cloze(Field const& field) -> bool
{
    ClozeDetector detector;

    for (auto const* node : field.children)
    {
        node->accept(detector);

        if (detector.contains_cloze())
            return true;
    }

    return false;
}

auto CardParser::determine_cardType(Card& card) -> CardType
{

    // TODO: this should be replaced by a Map which can be customised
    std::map<std::string, FieldType> keywordMap;

    for (auto& field : card.fields)
    {
        field.fieldType = CardParser::determine_fieldType(field, keywordMap);
    }

    if (card.fields.size() >= 2 && is_cloze_card(card))
        return CardType::Cloze;
    if (card.fields.size() >= 2)
    {

        return CardType::Basic;
    }
    return CardType::None;
}
auto CardParser::is_cloze_card(Card const& card) -> bool { return card.fields.at(1).fieldType == FieldType::Cloze; }

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

// TODO: this Would be a perfect place to use pre, because this function should probably be private and only ever be
// called by another function. So the mistake would not be in this Function be the one calling it.
auto CardParser::consume_card(Document const& document, std::size_t& i) -> Card
{
    Card result;

    // Cards out of bounds and not Starting
    if (i >= document.children.size())
    {
        throw std::runtime_error("Invalid index in consume_card");
    }
    auto* heading = dynamic_cast<Heading const*>(document.children.at(i).get());
    if (!heading)
    {
        throw std::runtime_error("Consume_card not called on level 2 heading");
    }

    // ## Question starts the card and belongs to its own field.
    result.fields.push_back(consume_field(document, i));

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

// TODO: this function should only be allowed to be called on a non empty document with a valid index
auto CardParser::consume_field(Document const& document, std::size_t& i) -> Field
{
    Field result;

    // Special case if the Question is consumed
    if (i < document.children.size())
    {
        auto* heading = dynamic_cast<Heading const*>(document.children.at(i).get());
        if (heading && heading->level == 2)
        {
            result.children.push_back(document.children.at(i).get());
            i++;
            return result;
        }
    }

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

auto ClozeDetector::contains_cloze() const -> bool { return found; }

void ClozeDetector::visit(BlockCloze const&) { found = true; }

void ClozeDetector::visit(InlineCloze const&) { found = true; }

void ClozeDetector::visit(Paragraph const& node)
{
    for (auto const& child : node.children)
        child->accept(*this);
}

void ClozeDetector::visit(Heading const& node)
{
    for (auto const& child : node.children)
        child->accept(*this);
}

void ClozeDetector::visit(InlineStrong const& node)
{
    for (auto const& child : node.children)
        child->accept(*this);
}

void ClozeDetector::visit(InlineEmphasis const& node)
{
    for (auto const& child : node.children)
        child->accept(*this);
}

AnkiRenderer::AnkiRenderer(Document const& document) { render(document); }

auto AnkiRenderer::render(Document const& node) -> std::string
{
    auto cards = CardParser::split_into_cards(node);

    for (auto& card : cards)
    {
        card.cardType = CardParser::determine_cardType(card);

        output += render_card(card);
    }

    return output;
}
auto AnkiRenderer::render_card(Card const& card) -> std::string
{
    switch (card.cardType)
    {
    case CardType::Basic:
    {
        return render_basic_card(card) + "\n";
    }
    case CardType::Cloze:
    {
        return render_cloze_card(card) + "\n";
    }
    }
    return {};
}

auto AnkiRenderer::render_basic_card(Card const& card) -> std::string
{
    std::string question;
    std::string answer;

    for (auto const& field : card.fields)
    {
        FieldRenderer fieldRenderer;
        switch (field.fieldType)
        {
        case FieldType::Question:
        {
            question += fieldRenderer.render(field);
            break;
        }
        case FieldType::Answer:
        {
            answer += fieldRenderer.render(field);
            break;
        }
        case FieldType::Extra:
        {
            Field heading;
            heading.children.push_back(field.children.at(0));
            Field rest;
            for (size_t i = 1; i < field.children.size(); i++)
            {
                rest.children.push_back(field.children.at(i));
            }
            answer += "<details><summary>";
            answer += fieldRenderer.render(heading); // content of Heading
            answer += "</summary>";
            answer += fieldRenderer.render(rest); // after heading
            answer += "</details>";
            break;
        }
        default:
        {
            answer += fieldRenderer.render(field);
            break;
        }
        }
    }

    std::string result;

    result += "\"imported Cards\";";
    result += "\"Automatic_Basic\";";
    result += "\"\";";
    result += "\"\";";

    result += '"';
    result += question;
    result += "\";";

    result += '"';
    result += answer;
    result += "\"";

    return result;
}

auto AnkiRenderer::render_cloze_card(Card const& card) -> std::string
{
    std::string question;
    std::string answer;

    for (auto const& field : card.fields)
    {
        FieldRenderer fieldRenderer;
        switch (field.fieldType)
        {
        case FieldType::Question:
        {
            question += fieldRenderer.render(field);
            break;
        }
        case FieldType::Cloze:
        {
            question += fieldRenderer.render(field);
            break;
        }
        default:
        {
            answer += fieldRenderer.render(field);
            break;
        }
        }
    }

    std::string result;

    result += "\"imported Cards\";";
    result += "\"Automatic_Cloze\";";
    result += "\"\";";
    result += "\"\";";

    result += '"';
    result += question;
    result += "\";";

    result += '"';
    result += answer;
    result += "\"";

    return result;
}

auto FieldRenderer::render(Field const& field) -> std::string
{
    output.clear();

    for (auto const* node : field.children)
    {
        node->accept(*this);
    }

    return output;
}

auto FieldRenderer::get_output() const -> std::string { return output; }

void FieldRenderer::visit(Paragraph const& node)
{
    output += "<p>";
    for (auto const& child : node.children)
    {
        child->accept(*this);
    }

    output += "</p>";
}

void FieldRenderer::visit(Heading const& node)
{
    output += "<h" + std::to_string(node.level) + ">";
    for (auto const& child : node.children)
    {
        child->accept(*this);
    }

    output += "</h" + std::to_string(node.level) + ">";
}

void FieldRenderer::visit(Text const& node)
{
    std::string result;
    result.reserve(node.text.size());

    for (char c : node.text)
    {
        switch (c)
        {
        case '&':
            result += "&amp;";
            break;
        case '<':
            result += "&lt;";
            break;
        case '>':
            result += "&gt;";
            break;
        case '"':
            result += "&quot;";
            break;
        case '\'':
            result += "&#39;";
            break;
        case '\n':
            result += "<br>";
            break;
        default:
            result += c;
            break;
        }
    }

    output += result;
}

void FieldRenderer::visit(BlockCode const& node)
{
    output += "<pre><code>";
    output += node.code;
    output += "</code></pre>";
}

void FieldRenderer::visit(BlockMath const& node)
{
    output += "\\[";
    output += node.equation;
    output += "\\]";
}
void FieldRenderer::visit(BlockCloze const& node)
{
    output += "{{c";
    output += std::to_string(clozeCount);
    output += "::";

    for (auto const& child : node.children)
    {
        child->accept(*this);
    }
    output += "}}";
    clozeCount++;
}

void FieldRenderer::visit(InlineMath const& node)
{
    output += "\\(";
    output += node.equation;
    output += "\\)";
}
void FieldRenderer::visit(InlineCode const& node)
{
    output += "<kdb>";
    output += node.code;
    output += "</kdb>";
}
void FieldRenderer::visit(InlineStrong const& node)
{
    output += "<strong>";

    for (auto const& child : node.children)
    {
        child->accept(*this);
    }
    output += "</strong>";
}
void FieldRenderer::visit(InlineEmphasis const& node)
{
    output += "<em>";

    for (auto const& child : node.children)
    {
        child->accept(*this);
    }
    output += "</em>";
}

void FieldRenderer::visit(InlineCloze const& node)
{

    output += "{{c";
    output += std::to_string(clozeCount);
    output += "::";

    for (auto const& child : node.children)
    {
        child->accept(*this);
    }
    output += "}}";
    clozeCount++;
}
