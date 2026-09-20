#include "visitor/AnkiRenderer.h"

#include "ast/Block.h"
#include "ast/Document.h"
#include "ast/Inline.h"

void AnkiRenderer::render(Document& node)
{
    for (size_t i = 0; i < node.children.size(); i++)
    {
        while (/*is not level two heading */)
        {
            // add the ast to the card
        }
    }
    for (/* for each card found*/)
    {
        // determine each field type and then the card type
        // output += render_card(); for each card type the render_card function should behave diffrently
    }
}
