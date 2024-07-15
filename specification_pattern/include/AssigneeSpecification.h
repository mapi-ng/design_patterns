#pragma once

#include "Issue.h"
#include "Specification.h"

class AssigneeSpecification : public Specification<Issue> {
 private:
  std::string assignee_;

 public:
  explicit AssigneeSpecification(std::string_view assignee)
      : assignee_(assignee) {}

  bool is_satisfied(Issue& issue) override {
    return issue.getAssignee() == assignee_;
  }
};
