#pragma once
#include "Issue.h"
#include "Specification.h"

class ReporterSpecification : public Specification<Issue> {
 private:
  std::string reporter_;

 public:
  explicit ReporterSpecification(std::string_view reporter)
      : reporter_(reporter) {}

  bool is_satisfied(Issue& issue) override {
    return issue.getReporter() == reporter_;
  }
};
