#include "YamlElement.h"

#include <sstream>

#include "YamlBuilder.h"

YamlBuilder YamlElement::create(std::string_view root_name) {
  return YamlBuilder{root_name};
}

void YamlElement::addElement(const YamlElement& element) {
  m_elements.emplace_back(element);
}

std::string YamlElement::str(int indent) const {
  std::ostringstream oss;
  std::string i(indent_size_ * indent, ' ');
  oss << i;
  if (!m_is_root) {
    oss << "- ";
  }
  oss << m_name << ":";

  if (m_value.size() > 0) {
    oss << " " << m_value << std::endl;
  }

  if (!m_elements.empty()) {
    oss << std::endl;
    for (const auto& e : m_elements) {
      oss << e.str(indent + 1);
    }
  }

  return oss.str();
}
