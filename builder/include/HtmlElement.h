#pragma once
#include <stddef.h>

#include <sstream>
#include <string>
#include <vector>

class HtmlBuilder;

class HtmlElement {
 private:
  std::string m_name;
  std::string m_text;
  std::vector<HtmlElement> m_elements;

  const size_t indent_size_ = 2;

 public:
  HtmlElement() = default;
  HtmlElement(std::string_view name, std::string_view text)
      : m_name(name), m_text(text) {}
  ~HtmlElement() = default;
  static HtmlBuilder build(std::string_view root_name);

  void setName(std::string_view name) { m_name = name; }
  void setText(std::string_view text) { m_text = text; }

  std::string getName() const { return m_name; }
  std::string getText() const { return m_text; }

  void addElement(const HtmlElement& element);

  std::string str(int indent = 0) const; };
