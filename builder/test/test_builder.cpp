#include <gtest/gtest.h>

#include <iostream>

#include "HtmlBuilder.h"

class BuilderFixture : public testing::Test {
 protected:
 public:
};

TEST_F(BuilderFixture, TestAddChild) {
  HtmlBuilder builder{"ul"};
  builder.AddChild("li", "hello");
  builder.AddChild("li", "world");

  auto fluent_builder = HtmlElement::build("div")
                            .AddChild("p", "paragraph1")
                            .AddChild("p", "paragraph2");

  std::cout << builder.str() << std::endl;
  std::cout << fluent_builder.str() << std::endl;
}