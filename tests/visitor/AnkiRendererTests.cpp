#include "ast/Block.h"
#include "ast/Document.h"
#include "visitor/AnkiRenderer.h"

#include <gtest/gtest.h>
#include <map>
#include <memory>

// functions to ease making tests
namespace
{

auto make_text(std::string text) -> std::unique_ptr<Text>
{
    auto phrase = std::make_unique<Text>();
    phrase->text = text;

    return phrase;
}

// TODO: These functions currently are a bit lack luster
auto make_heading(unsigned int level) -> std::unique_ptr<Heading>
{
    auto heading = std::make_unique<Heading>();
    heading->level = level;
    return heading;
}
auto make_heading(unsigned int level, std::vector<std::unique_ptr<Inline>> children) -> std::unique_ptr<Heading>
{
    auto heading = std::make_unique<Heading>();
    heading->level = level;
    heading->children = std::move(children);

    return heading;
}

auto make_paragraph() -> std::unique_ptr<Paragraph> { return std::make_unique<Paragraph>(); }
} // namespace

/* --- Tests for CardParser --- */

/* -- Tests for split_into_cards -- */
TEST(CardParserTests, EmptyDocumentProducesNoCards)
{
    Document document;

    auto cards = CardParser::split_into_cards(document);

    EXPECT_TRUE(cards.empty());
}

TEST(CardParserTests, SplitIntoCards_DocumentWithoutLevel2HeadingProducesNoCards)
{
    Document document;
    auto heading1 = make_heading(3);

    document.children.push_back(std::move(heading1));

    auto cards = CardParser::split_into_cards(document);

    EXPECT_TRUE(cards.empty());
}

TEST(CardParserTests, SplitIntoCards_ExampleSplitsCorrectly)
{
    Document document;

    auto heading1 = make_heading(2);
    auto paragraph1 = make_paragraph();
    auto paragraph2 = make_paragraph();
    auto heading2 = make_heading(3);
    auto paragraph3 = make_paragraph();
    auto heading3 = make_heading(2);

    document.children.push_back(std::move(heading1));
    document.children.push_back(std::move(paragraph1));
    document.children.push_back(std::move(paragraph2));
    document.children.push_back(std::move(heading2));
    document.children.push_back(std::move(paragraph3));
    document.children.push_back(std::move(heading3));

    auto cards = CardParser::split_into_cards(document);

    EXPECT_TRUE(cards.size() == 2);
    EXPECT_TRUE(cards.at(0).fields.size() == 3);
    EXPECT_TRUE(cards.at(1).fields.size() == 1);
}

/* -- Tests for consume_card -- */

TEST(CardParserTests, ConsumeCard_EmptyDocumentThrowsRuntimeError)
{
    Document document;

    size_t i = 0;
    EXPECT_THROW(CardParser::consume_card(document, i), std::runtime_error);
}
TEST(CardParserTests, ConsumeCard_DocumentAtIndexNotLevel2HeadingThrowsRuntimeError)
{
    Document document;
    document.children.push_back(make_paragraph());

    size_t i = 0;

    ASSERT_TRUE(document.children.size() == 1);
    EXPECT_THROW(CardParser::consume_card(document, i), std::runtime_error);
}

TEST(CardParserTests, ConsumeCard_ExampleParsesCorrectly)
{
    Document document;

    auto heading1 = make_heading(2);
    auto paragraph1 = make_paragraph();
    auto paragraph2 = make_paragraph();
    auto heading2 = make_heading(3);
    auto paragraph3 = make_paragraph();
    auto heading3 = make_heading(2);

    document.children.push_back(std::move(heading1));
    document.children.push_back(std::move(paragraph1));
    document.children.push_back(std::move(paragraph2));
    document.children.push_back(std::move(heading2));
    document.children.push_back(std::move(paragraph3));
    document.children.push_back(std::move(heading3));

    size_t i = 0;

    auto card = CardParser::consume_card(document, i);

    ASSERT_TRUE(document.children.size() == 6);
    EXPECT_TRUE(card.fields.size() == 3);
    EXPECT_TRUE(i == 5);
}

/* -- Tests for consume_field -- */

TEST(CardParserTests, ConsumeField_EmptyDocumentProducesNoFields)
{
    Document document;
    size_t i = 0;

    auto field = CardParser::consume_field(document, i);

    EXPECT_TRUE(i == 0);
    EXPECT_TRUE(field.children.empty());
}

TEST(CardParserTests, ConsumeField_DocumentWithOnlyLevel3HeadingReturnsOnlyHeading)
{
    Document document;

    auto heading = make_heading(3);
    document.children.push_back(std::move(heading));
    size_t i = 0;

    auto field = CardParser::consume_field(document, i);

    // TODO: currently only checks whether the iterator was advanced correctly
    EXPECT_TRUE(i == 1);
}

TEST(CardParserTests, ConsumeField_DocumentWithOnlyLevel2HeadingReturnsOnlyHeading)
{
    Document document;

    auto heading = make_heading(2);
    document.children.push_back(std::move(heading));
    size_t i = 0;

    auto field = CardParser::consume_field(document, i);

    // TODO: currently only checks whether the iterator was advanced correctly
    EXPECT_TRUE(i == 1);
}

TEST(CardParserTests, ConsumeField_DocumentWithOnlyOneParagraph)
{
    Document document;

    auto paragraph = make_paragraph();
    document.children.push_back(std::move(paragraph));
    size_t i = 0;

    auto field = CardParser::consume_field(document, i);

    EXPECT_TRUE(i == 1);
}

TEST(CardParserTests, ConsumeField_DocumentWithQuestionAndPagraphOnlyAdvancesOne)
{
    Document document;

    auto heading = make_heading(2);
    auto paragraph = make_paragraph();
    document.children.push_back(std::move(heading));
    document.children.push_back(std::move(paragraph));
    size_t i = 0;

    auto field = CardParser::consume_field(document, i);

    EXPECT_TRUE(document.children.size() == 2);

    EXPECT_TRUE(i == 1);

    auto field2 = CardParser::consume_field(document, i);

    EXPECT_TRUE(i == 2);
}

TEST(CardParserTests, ConsumeField_DocumentWithLevel3HeadingAdvancesTillEndOfDocument)
{
    Document document;

    auto heading = make_heading(3);
    auto paragraph = make_paragraph();
    document.children.push_back(std::move(heading));
    document.children.push_back(std::move(paragraph));
    size_t i = 0;

    auto field = CardParser::consume_field(document, i);

    EXPECT_TRUE(document.children.size() == 2);

    EXPECT_TRUE(i == 2);
}

TEST(CardParserTests, ConsumeField_StopsbeforeNextLevel3Heading)
{

    Document document;

    auto heading1 = make_heading(3);
    auto paragraph1 = make_paragraph();
    auto paragraph2 = make_paragraph();
    auto heading2 = make_heading(3);

    document.children.push_back(std::move(heading1));
    document.children.push_back(std::move(paragraph1));
    document.children.push_back(std::move(paragraph2));
    document.children.push_back(std::move(heading2));
    size_t i = 0;

    auto field = CardParser::consume_field(document, i);

    EXPECT_TRUE(document.children.size() == 4);

    EXPECT_TRUE(i == 3);
}

/* -- Tests for determine_fieldType -- */

TEST(CardParserTests, DetermineFieldType_Level2HeadingReturnsQuestion)
{
    Field field;
    std::map<std::string, FieldType> keywordMap;

    Heading heading;
    heading.level = 2;
    Heading* heading_ptr = &heading;

    field.children.push_back(heading_ptr);

    auto fieldType = CardParser::determine_fieldType(field, keywordMap);

    EXPECT_TRUE(fieldType == FieldType::Question);
}

TEST(CardParserTests, DetermineFieldType_ParagraphWithoutClozeIsAnswer)
{
    Field field;
    std::map<std::string, FieldType> keywordMap;

    Paragraph paragraph;
    Paragraph* paragraph_ptr = &paragraph;

    field.children.push_back(paragraph_ptr);

    auto fieldType = CardParser::determine_fieldType(field, keywordMap);

    EXPECT_TRUE(fieldType == FieldType::Answer);
}
