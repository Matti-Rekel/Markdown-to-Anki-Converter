#include "InlineParser.h"
#include "InlineMathParser.h"
#include <iostream>

auto InlineParser::parse_inline(Cursor& cursor) -> std::unique_ptr<Inline>
{
    if (InlineMathParser::is_inlineMath(cursor))
        return InlineMathParser::parse(cursor);

    return TextParser::parse(cursor);
}
