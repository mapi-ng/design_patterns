#include "HtmlElement.h"
#include "HtmlBuilder.h"

HtmlBuilder HtmlElement::build(std::string_view root_name) {
  return HtmlBuilder{root_name};
}
void HtmlElement::addElement(const HtmlElement& element) {
  m_elements.emplace_back(element);
}

std::string HtmlElement::str(int indent) const {
  std::ostringstream oss;
  std::string i(indent_size_ * indent, ' ');
  oss << i << "<" << m_name << ">" << std::endl;

  if (m_text.size() > 0)
    oss << std::string(indent_size_ * (indent + 1), ' ') << m_text << std::endl;

  for (const auto& e : m_elements) oss << e.str(indent + 1);

  oss << i << "</" << m_name << ">" << std::endl;
  return oss.str();
}
