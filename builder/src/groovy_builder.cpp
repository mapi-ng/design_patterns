#include <iostream>
#include <vector>

struct Tag {
  std::string name_;
  std::string text_;
  std::vector<Tag> children_;
  std::vector<std::pair<std::string, std::string>> attributes_;

  friend std::ostream& operator<<(std::ostream& os, const Tag& tag) {
    os << "<" << tag.name_;

    for (const auto& att : tag.attributes_)
      os << " " << att.first << "=\"" << att.second << "\"";

    if (tag.children_.size() == 0 && tag.text_.length() == 0) {
      os << "/>" << std::endl;
    } else {
      os << ">" << std::endl;

      if (tag.text_.length())
        os << tag.text_ << std::endl;

      for (const auto& child : tag.children_)
        os << child;

      os << "</" << tag.name_ << ">" << std::endl;
    }

    return os;
  }

 protected:
 public:
  Tag(const std::string& name, const std::string& text) : name_(name), text_(text) {}
  Tag(const std::string& name, const std::vector<Tag>& children) : name_(name), children_(children) {}
};

struct P : Tag {
  P(const std::string& text) : Tag("p", text) {}
  P(std::initializer_list<Tag> children) : Tag{"p", children} {}
};

struct Img : Tag {
  explicit Img(const std::string& url) : Tag{"img", ""} {
    attributes_.emplace_back(std::make_pair("src", url));
  }
};

int main(int argc, char* argv[]) {
  std::cout <<
  P{
    Img{"http://asdf.def.png"}
  }
  << std::endl;
  return 0;
}