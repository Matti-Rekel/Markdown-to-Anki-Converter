#include "InlineParser.h"
#include "InlineMathParser.h"
#include <memory>

auto InlineParser::parse_inline(Cursor& cursor) -> std::unique_ptr<Inline>
{
    if (InlineMathParser::is_inlineMath(cursor))
        return InlineMathParser::parse(cursor);

    return TextParser::parse(cursor);
}
auto InlineParser::starts_inline(Cursor cursor) -> bool
{
    return InlineMathParser::is_inlineMath(cursor); // In Case of expansion this line needs to be expanded.
}
auto TextParser::parse(Cursor& cursor) -> std::unique_ptr<Text>
{
    auto result = std::make_unique<Text>();
    std::string text;

    while (!cursor.is_end_of() && !InlineParser::starts_inline(cursor))
    {
        text += cursor.consume_range(1);
    }

    result->text = text;

    return result;
}
