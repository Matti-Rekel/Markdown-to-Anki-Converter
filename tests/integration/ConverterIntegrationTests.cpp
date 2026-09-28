#include <gtest/gtest.h>

#include "ast/Block.h"
#include "parser/BlockParser/BlockParser.h"
#include "parser/InlineParser/InlineParser.h"
#include "parser/Parser.h"
#include "visitor/AnkiRenderer.h"

TEST(ConverterIntegrationTests, DetectsInlineMath)
{
    FieldRenderer renderer;
    Cursor cursor("$a^2$");
    const auto content = InlineParser::parse_inline(cursor);

    const auto* inlineMath = dynamic_cast<const InlineMath*>(content.get());

    ASSERT_NE(inlineMath, nullptr);

    renderer.visit(*inlineMath);

    EXPECT_EQ(renderer.get_output(), "\\(a^2\\)");
}

TEST(ConverterIntegrationTests, DetectsInlineCode)
{
    FieldRenderer renderer;
    Cursor cursor("`a^2`");
    const auto content = InlineParser::parse_inline(cursor);

    const auto* inlineCode = dynamic_cast<const InlineCode*>(content.get());

    ASSERT_NE(inlineCode, nullptr);

    renderer.visit(*inlineCode);

    EXPECT_EQ(renderer.get_output(), "<kdb>a^2</kdb>");
}
TEST(BlockParserTest, ParsesParagraph)
{
    FieldRenderer renderer;
    Cursor cursor{"One line\n"};

    auto content = BlockParser::parse_block(cursor);

    const auto* paragraph = dynamic_cast<const Paragraph*>(content.get());

    ASSERT_NE(paragraph, nullptr);
    renderer.visit(*paragraph);

    EXPECT_EQ(renderer.get_output(), "<p>One line</p>");
}

TEST(ConverterIntegrationTests, DetectsParagraph)
{
    FieldRenderer renderer;

    std::string text = "One line\n";
    text += "\n";
    text += "third line\n";

    Document document = Parser::parse(text);

    ASSERT_EQ(document.children.size(), 2);

    for (auto const& content : document.children)
    {

        const auto* paragraph = dynamic_cast<const Paragraph*>(content.get());

        ASSERT_NE(paragraph, nullptr);

        renderer.visit(*paragraph);
    }

    EXPECT_EQ(renderer.get_output(), "<p>One line</p><p>third line</p>");
}

// --- Parse to Card ---

TEST(ConverterIntegrationTests, MarkdownToCardNoQuestionNoCard)
{
    std::string markdown;
    markdown = "Antwort";

    Document document = Parser::parse(markdown);
    AnkiRenderer renderer;
    auto output = renderer.render(document);

    EXPECT_EQ(output, "");
}

TEST(ConverterIntegrationTests, MarkdownToCardOnlyQuestionNoCard)
{
    std::string markdown;
    markdown = "## Frage\n";

    Document document = Parser::parse(markdown);
    AnkiRenderer renderer;
    auto output = renderer.render(document);

    EXPECT_EQ(output, "");
}

TEST(ConverterIntegrationTests, MarkdownToCardExample)
{
    std::string markdown;
    markdown = "## Frage\n";
    markdown += "Antwort";

    Document document = Parser::parse(markdown);
    AnkiRenderer renderer;
    auto output = renderer.render(document);

    EXPECT_EQ(output, "\"imported Cards\";\"Automatic_Basic\";\"\";\"\";\"<h2>Frage</h2>\";\"<p>Antwort</p>\"\n");
}
