#include "ParseCards.h"

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

auto parse_into_cards(std::string const &document,
                      std::map<std::string, fields> keywords)
    -> std::vector<Card> {
  std::vector<Card> result;
  auto cardContents = split_by_headings(document);

  for (auto card : cardContents) {
    result.push_back(split_text(card, keywords));
  }
  return result;
}

std::vector<std::string> split_by_headings(const std::string &text) {
  std::vector<std::string> result;

  std::size_t start = text.find("## ");

  while (start != std::string::npos) {
    // Find the next ## that starts a line.
    std::size_t next = text.find("\n## ", start + 3);

    if (next == std::string::npos) {
      result.push_back(text.substr(start));
      break;
    }

    result.push_back(text.substr(start, next - start));

    // +1 skips the newline but keeps the ##
    start = next + 1;
  }

  return result;
}

auto split_text(std::string text, std::map<std::string, fields> keywords)
    -> Card {
  Card res;

  size_t index = 0;
  res.Question = find_question(text, index);
  res.Answer = find_answer(text, index);
  std::map<fields, std::string> extraFields =
      find_extra_fields(text, index, keywords);

  for (fields a : {fields::Question, fields::Prerequisites, fields::Hint,
                   fields::Answer, fields::Add_Information, fields::Source}) {
    auto it = extraFields.find(a);
    if (it != extraFields.end()) {
      switch (a) {
      case fields::Prerequisites:
        res.Prerequisites = extraFields.at(fields::Prerequisites);
        break;
      case fields::Hint:
        res.Hint = extraFields.at(fields::Hint);
        break;
      case fields::Add_Information:
        res.Add_Information = extraFields.at(fields::Add_Information);
        break;
      case fields::Source:
        res.Source = extraFields.at(fields::Source);
        break;
      }
    }
  }
  return res;
}

auto find_question(std::string const &text, size_t &index) -> std::string {
  auto beginning = index;

  auto end = text.find("\n\n", index);

  if (end == std::string::npos) {
    index = text.length();
    return text.substr(beginning);
  }

  index = end;
  return text.substr(beginning, end - beginning);
}

auto find_answer(std::string const &text, size_t &index) -> std::string {
  auto beginning = index;

  auto end = text.find("\n### ", index);

  if (end == std::string::npos) {
    index = text.length();
    return text.substr(beginning);
  }

  index = end;
  return text.substr(beginning, end - beginning);
}

auto find_extra_fields(std::string text, size_t &index,
                       std::map<std::string, fields> keywords)
    -> std::map<fields, std::string> {
  std::map<fields, std::string> res;
  std::vector<std::string> extra = split_into_extra(text, index);
  for (auto a : extra) {
    auto b = find_keyword(a, keywords);
    res.insert({b.first, b.second});
  }
  return res;
}

auto split_into_extra(std::string text, size_t index)
    -> std::vector<std::string> {
  std::vector<size_t> i;
  while (index < text.length()) {
    if ((index + 3 < text.length()) &&
        (text.at(index - 1) == '\n' && text.at(index) == '#' &&
         text.at(index + 1) == '#' && text.at(index + 2) == '#' &&
         text.at(index + 3) == ' ')) {
      i.push_back(index);
    }
    index++;
  }
  i.push_back(text.length());
  return get_extra(text, i);
}

auto get_extra(std::string &text, std::vector<size_t> i)
    -> std::vector<std::string> {
  std::vector<std::string> res;
  size_t index = i.at(0);
  for (size_t j = 1; j < i.size(); j++) {
    std::string s = "";
    while (index < i.at(j)) {
      s.push_back(text.at(index));
      index++;
    }
    res.push_back(s);
    index++;
  }
  return res;
}

auto find_keyword(std::string text, std::map<std::string, fields> keywords)
    -> std::pair<fields, std::string> {
  std::pair<fields, std::string> res;
  std::string keyword = "";
  std::string txt = "";
  size_t index = 0;
  while (index < text.length() && text.at(index) != '\n') {
    keyword.push_back(text.at(index));
    index++;
  }
  while (index < text.length()) {
    txt.push_back(text.at(index));
    index++;
  }
  auto it = keywords.find(keyword);
  if (it != keywords.end()) {
    res = std::pair<fields, std::string>{keywords.at(keyword), txt};
  } else
    std::cout << "Invalid Card marker";
  return res;
}
