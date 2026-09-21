#include "ast/Block.h"
#include "ast/Document.h"
#include "visitor/AnkiRenderer.h"

#include <gtest/gtest.h>

namespace
{
auto make_heading(unsigned int level) -> std::unique_ptr<Heading>
{
    auto heading = std::make_unique<Heading>();
    heading->level = level;
    return heading;
}

auto make_paragraph() -> std::unique_ptr<Paragraph> { return std::make_unique<Paragraph>(); }
} // namespace

TEST(AnkiRendererSplitIntoCardsTest, EmptyDocumentProducesNoCards)
{
    Document document;
    AnkiRenderer renderer;

    auto cards = CardParser::split_into_cards(document);

    EXPECT_TRUE(cards.empty());
}
