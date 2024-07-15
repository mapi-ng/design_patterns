#pragma once
#include "HtmlElement.h"

class HtmlBuilder {
 private:
  HtmlElement m_root;

 public:
  explicit HtmlBuilder(std::string_view root_name);
  HtmlBuilder& AddChild(std::string_view child_name,
                        std::string_view child_text);

  std::string str() const;
};
