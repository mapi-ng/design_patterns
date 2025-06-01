#pragma once

#include "Filter.h"
#include "Issue.h"

class IssueFilter : public Filter<Issue> {
 public:
  std::vector<Issue> filter(std::vector<Issue> issues,
                            Specification<Issue>& specification) override {
    std::vector<Issue> filtered_issues;

    for (auto& issue : issues) {
      if (specification.is_satisfied(issue)) {
        filtered_issues.push_back(issue);
      }
    }

    return filtered_issues;
  }
};
