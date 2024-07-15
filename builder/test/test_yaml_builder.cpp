#include <gtest/gtest.h>

#include "YamlBuilder.h"

TEST(YamlBuilderTest, TestOk) {
  YamlBuilder builder("config");
  builder.AddChild("entry1", "value1");
  builder.AddChild("entry2", "value2");

  std::cout << builder.str() << std::endl;

  // Create builder from static 'create' method
  // and chain subsequent calls
  auto fluent_builder = YamlElement::create("fluent")
                            .AddChild("entry1", "value1")
                            .AddChild("entry2", "value2");

  std::cout << fluent_builder.str() << std::endl;

  // Create a builder using 'build' method
  YamlElement yaml_element1 = fluent_builder.build();

  // Try to add nested element
  fluent_builder.AddChild(yaml_element1);
  std::cout << fluent_builder.str() << std::endl;

  std::string expected_yaml{
      "fluent:\n"
      "  - entry1: value1\n"
      "  - entry2: value2\n"
      "  fluent:\n"
      "    - entry1: value1\n"
      "    - entry2: value2\n"};

  auto fluent_str = fluent_builder.str();
  EXPECT_EQ(expected_yaml, fluent_str);
}
