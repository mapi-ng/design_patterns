#include "HtmlBuilder.h"

HtmlBuilder::HtmlBuilder(std::string_view root_name) {
  m_root.setName(root_name);
}

HtmlBuilder& HtmlBuilder::AddChild(std::string_view child_name,
                                   std::string_view child_text) {
  HtmlElement e{child_name, child_text};
  m_root.addElement(e);
  return *this;
}

std::string HtmlBuilder::str() const { return m_root.str(); }