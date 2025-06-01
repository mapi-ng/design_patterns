#pragma once
#include <string>
#include <vector>

class YamlBuilder;

class YamlElement {
 private:
  friend YamlBuilder;

  std::string m_name;
  std::string m_value;
  std::vector<YamlElement> m_elements;

  bool m_is_root{false};
  const size_t indent_size_ = 2;

  YamlElement() = default;
  YamlElement(std::string_view name, std::string_view value,
              bool is_root = false)
      : m_name{name}, m_value{value}, m_is_root{is_root} {}

 public:
  static YamlBuilder create(std::string_view root_name);

  void setName(std::string_view name) { m_name = name; }
  void setText(std::string_view text) { m_value = text; }

  std::string getName() const { return m_name; }
  std::string getText() const { return m_value; }

  void setRoot(bool is_root) { m_is_root = is_root; }
  bool isRoot() const { return m_is_root; }

  void addElement(const YamlElement& element);

  std::string str(int indent = 0) const;
};
