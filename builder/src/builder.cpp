#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class HtmlElement {
 private:
  friend class HtmlBuilder;
  std::string name_;
  std::string text_;
  std::vector<HtmlElement> elements_;

  const size_t indent_size_ = 2;

  HtmlElement() = default;
  HtmlElement(const std::string& name, const std::string& text)
      : name_(name), text_(text) {}

 public:
  void setName(const std::string& name) { name_ = name; }
  void setText(const std::string& text) { text_ = text; }

  std::string getName() const { return name_; }
  std::string getText() const { return text_; }
  void addElement(const HtmlElement& e) { elements_.emplace_back(e); }

  std::string str(int indent = 0) const {
    std::ostringstream oss;
    std::string i(indent_size_ * indent, ' ');
    oss << i << "<" << name_ << ">" << std::endl;

    if (text_.size() > 0)
      oss << std::string(indent_size_ * (indent + 1), ' ') << text_ << std::endl;

    for (const auto& e : elements_)
      oss << e.str(indent + 1);

    oss << i << "</" << name_ << ">" << std::endl;
    return oss.str();
  }

  // Don't used, because creates circular dependency
  // Anyway, why would HtmlElement create a HtmlBuilder?
  //HtmlBuilder create(std::string root_name);
};

class HtmlBuilder {
 private:
  HtmlElement root_;

 public:
  HtmlBuilder(std::string root_name) {
    root_.setName(root_name);
  }

  HtmlBuilder& addChild(std::string child_name, std::string child_text) {
    HtmlElement e{child_name, child_text};
    root_.addElement(e);

    return *this;
  }

  std::string str() const {
    return root_.str();
  }

  operator HtmlElement() const { return root_; }
};

int main(int argc, char* argv[]) {
  HtmlBuilder builder{"ul"};
  builder.addChild("li", "hello")
      .addChild("li", "world");

  std::cout << builder.str() << std::endl;

  HtmlElement list_el = builder; // Implicit conversion of HtmlBuilder to HtmlElement would be ok.
  std::cout << list_el.str() << std::endl;

  // We don't really want HtmlElement to 'create' HtmlBuilder.
  //auto builer2 = HtmlElement::create("ul").addChild("li", "test");
  //HtmlElement builer3 = HtmlElement::create("ul").addChild("li", "test");
  //HtmlElement builer4 = HtmlElement::create("ul").addChild("li", "test").build();

  return 0;
}
