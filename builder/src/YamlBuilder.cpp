#include "YamlBuilder.h"

YamlBuilder::YamlBuilder(std::string_view root_name) {
  m_root.setName(root_name);
  m_root.setRoot(true);
}

YamlElement YamlBuilder::build() const { return m_root; }

YamlBuilder& YamlBuilder::AddChild(std::string_view child_name,
                                   std::string_view child_value) {
  YamlElement e{child_name, child_value};
  m_root.addElement(e);
  return *this;
}

YamlBuilder& YamlBuilder::AddChild(const YamlElement& child_value) {
  m_root.addElement(child_value);
  return *this;
}

std::string YamlBuilder::str() const { return m_root.str(); }