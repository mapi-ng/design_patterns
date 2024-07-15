#pragma once

#include "Issue.h"
#include "Specification.h"

class PriorityNotSpecification : public Specification<Issue> {
 private:
  Issue::Priority priority_;

 public:
  explicit PriorityNotSpecification(Issue::Priority priority) : priority_(priority) {}

  bool is_satisfied(Issue& issue) override {
    return issue.getPriority() != priority_;
  }
};
