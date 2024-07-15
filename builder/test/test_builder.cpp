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

  std::cout << builder.str() << std::endl;
}