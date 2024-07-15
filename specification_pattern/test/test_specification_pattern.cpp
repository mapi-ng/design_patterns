#include <gtest/gtest.h>

#include "AndSpecification.h"
#include "AssigneeSpecification.h"
#include "IssueFilter.h"
#include "PriorityNotSpecification.h"
#include "PrioritySpecification.h"
#include "ReporterSpecification.h"

class SpecificationFixture : public testing::Test {
 protected:
  IssueFilter m_filter;
  std::vector<Issue> issues = {
      {"ISS1", "Marcin", "Tomasz", Issue::Type::Bug, Issue::Priority::Low},
      {"ISS2", "Marcin", "Mariusz", Issue::Type::Story,
       Issue::Priority::Medium},
      {"ISS3", "Robert", "Mariusz", Issue::Type::Task, Issue::Priority::High},
      {"ISS4", "Mariusz", "Jonasz", Issue::Type::Task, Issue::Priority::High},
      {"ISS5", "Marcin", "Jonasz", Issue::Type::Task, Issue::Priority::High},
      {"ISS5", "Marcin", "Jonasz", Issue::Type::Task, Issue::Priority::Low},
  };

 public:
};

TEST_F(SpecificationFixture, TestAssignee) {
  AssigneeSpecification spec_by_assignee("Mariusz");

  auto filtered_by_assignee = m_filter.filter(issues, spec_by_assignee);

  std::cout << "Issues with assignee Mariusz: \n";
  for (auto& issue : filtered_by_assignee) {
    std::cout << issue.getKey() << std::endl;
  }
}

TEST_F(SpecificationFixture, TestReporter) {
  ReporterSpecification spec_by_reporter("Marcin");

  auto filtered_by_assignee = m_filter.filter(issues, spec_by_reporter);

  std::cout << "Issues with assignee Mariusz: \n";
  for (auto& issue : filtered_by_assignee) {
    std::cout << issue.getKey() << std::endl;
  }
}

TEST_F(SpecificationFixture, TestPriority) {
  PrioritySpecification spec_by_priority(Issue::Priority::High);

  auto filtered_by_priority = m_filter.filter(issues, spec_by_priority);

  std::cout << "Issues with priority High: \n";
  for (auto& issue : filtered_by_priority) {
    std::cout << issue.getKey() << std::endl;
  }
}

TEST_F(SpecificationFixture, TestPriorityNot) {
  PriorityNotSpecification spec_by_priority_not(Issue::Priority::Medium);

  auto filtered_by_priority_not = m_filter.filter(issues, spec_by_priority_not);

  std::cout << "Issues with priority NOT Medium: \n";
  for (auto& issue : filtered_by_priority_not) {
    std::cout << issue.getKey() << std::endl;
  }
}

TEST_F(SpecificationFixture, TestReporterAndPriority) {
  ReporterSpecification spec_by_reporter("Marcin");
  PrioritySpecification spec_by_priority(Issue::Priority::High);
  AndSpecification<Issue> spec_priority_and_reporter(spec_by_reporter,
                                                     spec_by_priority);

  auto filtered_by_priority_and_reporter =
      m_filter.filter(issues, spec_priority_and_reporter);

  std::cout << "Issues with priority High and reporter Marcin: \n";
  for (auto& issue : filtered_by_priority_and_reporter) {
    std::cout << issue.getKey() << std::endl;
  }
}

TEST_F(SpecificationFixture, TestOk) {
  /* Leads to segmentation fault - references to non-existing objects within
  AndSpecification
  auto spec = AssigneeSpecification("Jonasz") &&
  PrioritySpecification(Issue::Priority::High);
  */

  std::shared_ptr<Specification<Issue>> assignee_spec =
      std::make_shared<AssigneeSpecification>("Jonasz");
  std::shared_ptr<Specification<Issue>> prio_spec =
      std::make_shared<PrioritySpecification>(Issue::Priority::High);
  auto spec = *assignee_spec && *prio_spec;
  auto filtered_by_priority_and_reporter_operator =
      m_filter.filter(issues, spec);

  std::cout << "Issues with priority High and assignee Jonasz: \n";
  for (auto& issue : filtered_by_priority_and_reporter_operator) {
    std::cout << issue.getKey() << std::endl;
  }
}