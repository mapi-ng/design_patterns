#pragma once
#include "HtmlElement.h"

class HtmlBuilder {
 private:
  HtmlElement m_root;

 public:
  HtmlBuilder(std::string_view root_name) { m_root.setName(root_name); }

  void AddChild(std::string_view child_name, std::string_view child_text) {
    HtmlElement e{child_name, child_text};
    m_root.addElement(e);
  }

  std::string str() const { return m_root.str(); }
};
