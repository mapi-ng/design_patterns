#pragma once
#include "YamlElement.h"

class YamlBuilder {
 private:
  YamlElement m_root;

 public:
  explicit YamlBuilder(std::string_view root_name);
  YamlBuilder& AddChild(std::string_view child_name,
                        std::string_view child_value);

  operator YamlElement() const { return m_root; }
  YamlElement build();
  std::string str() const;
};
