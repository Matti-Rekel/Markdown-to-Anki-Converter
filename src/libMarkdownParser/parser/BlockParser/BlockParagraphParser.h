#include "Cursor.h"
#include "ast/Block.h"
#include <memory>

class ParagraphParser
{
  public:
    static auto parse(Cursor& cursor) -> std::unique_ptr<Paragraph>;
    static auto parse_content(Cursor& cursor) -> std::vector<std::unique_ptr<Inline>>;

  private:
    static auto determine_construct_range(Cursor cursor) -> Range;
};
