#pragma once
#include <stddef.h>

#include <sstream>
#include <string>
#include <vector>

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

  void setName(std::string_view name) { m_name = name; }
  void setText(std::string_view text) { m_text = text; }

  std::string getName() const { return m_name; }
  std::string getText() const { return m_text; }

  void addElement(const HtmlElement& element) {
    m_elements.emplace_back(element);
  }

  std::string str(int indent = 0) const {
    std::ostringstream oss;
    std::string i(indent_size_ * indent, ' ');
    oss << i << "<" << m_name << ">" << std::endl;

    if (m_text.size() > 0)
      oss << std::string(indent_size_ * (indent + 1), ' ') << m_text
          << std::endl;

    for (const auto& e : m_elements) oss << e.str(indent + 1);

    oss << i << "</" << m_name << ">" << std::endl;
    return oss.str();
  }
};
