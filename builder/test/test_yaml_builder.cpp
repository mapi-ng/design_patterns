#include <gtest/gtest.h>

#include "YamlBuilder.h"

TEST(YamlBuilderTest, VisualTest) {
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

  // Create a builder by implicit conversion of builder into element
  YamlElement yaml_element2 = fluent_builder;
}