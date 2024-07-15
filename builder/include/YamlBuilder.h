#pragma once
#include "YamlElement.h"

class YamlBuilder {
 private:
  YamlElement m_root;

 public:
  explicit YamlBuilder(std::string_view root_name);
  YamlBuilder& AddChild(std::string_view child_name,
                        std::string_view child_value);
  YamlBuilder& AddChild(const YamlElement& child_value);

  YamlElement build() const;
  std::string str() const;
};
