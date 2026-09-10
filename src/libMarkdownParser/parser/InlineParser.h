
#include "Cursor.h"
#include "ast/Inline.h"
#include <memory>

class InlineParser
{
  public:
    static auto parse_inline(Cursor& cursor, Range range) -> std::unique_ptr<Inline>;
};

class TextParser
{
  public:
    static auto parse(Cursor& cursor, Range range) -> std::unique_ptr<Text>;
};
