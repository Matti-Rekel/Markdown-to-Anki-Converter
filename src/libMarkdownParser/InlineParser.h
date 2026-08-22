#ifndef INLINE_PARSER_H
#define INLINE_PARSER_H

#include <string>

struct Text {
    std::string value;
};

struct Emphasis {
    std::vector<Inline> children;
};

struct Strong {
    std::vector<Inline> children;
};

struct Code {
    std::string value;
};

struct Link {
    std::string url;
    std::vector<Inline> children;
};

using Inline = std::variant<
    Text,
    Emphasis,
    Strong,
    Code,
    Link
>;

#endif
