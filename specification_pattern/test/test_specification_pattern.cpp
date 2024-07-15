#include <gtest/gtest.h>

#include "AndSpecification.h"
#include "AssigneeSpecification.h"
#include "IssueFilter.h"
#include "PriorityNotSpecification.h"
#include "PrioritySpecification.h"
#include "ReporterSpecification.h"

void expectIssueKeys(const std::vector<Issue> issues,
                     const std::vector<std::string_view>& expected_keys) {
  for (auto& issue : issues) {
    auto it = std::find_if(
        expected_keys.begin(), expected_keys.end(),
        [&issue](std::string_view a) { return a == issue.getKey(); });
    EXPECT_TRUE(it != expected_keys.end());
  }
}

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
      {"ISS6", "Marcin", "Jonasz", Issue::Type::Task, Issue::Priority::Low},
  };

 public:
};

TEST_F(SpecificationFixture, TestAssignee) {
  AssigneeSpecification spec_by_assignee("Mariusz");

  auto filtered_by_assignee = m_filter.filter(issues, spec_by_assignee);

  expectIssueKeys(filtered_by_assignee, {"ISS2", "ISS3"});
}

TEST_F(SpecificationFixture, TestReporter) {
  ReporterSpecification spec_by_reporter("Marcin");

  auto filtered_by_reporter = m_filter.filter(issues, spec_by_reporter);

  expectIssueKeys(filtered_by_reporter, {"ISS1", "ISS2", "ISS5", "ISS6"});
}

TEST_F(SpecificationFixture, TestPriority) {
  PrioritySpecification spec_by_priority(Issue::Priority::High);

  auto filtered_by_priority = m_filter.filter(issues, spec_by_priority);

  expectIssueKeys(filtered_by_priority, {"ISS3", "ISS4", "ISS5"});
}

TEST_F(SpecificationFixture, TestPriorityNot) {
  PriorityNotSpecification spec_by_priority_not(Issue::Priority::Medium);

  auto filtered_by_priority_not = m_filter.filter(issues, spec_by_priority_not);

  expectIssueKeys(filtered_by_priority_not,
                  {"ISS1", "ISS3", "ISS4", "ISS5", "ISS6"});
}

TEST_F(SpecificationFixture, TestReporterAndPriority) {
  ReporterSpecification spec_by_reporter("Marcin");
  PrioritySpecification spec_by_priority(Issue::Priority::High);
  AndSpecification<Issue> spec_priority_and_reporter(spec_by_reporter,
                                                     spec_by_priority);

  auto filtered_by_priority_and_reporter =
      m_filter.filter(issues, spec_priority_and_reporter);

  expectIssueKeys(filtered_by_priority_and_reporter, {"ISS5"});
}

TEST_F(SpecificationFixture, TestAndOperator) {
  // const_cast used to suppress error:
  // error: cannot bind non-const lvalue reference of type
  // ‘Specification<Issue>&’ to an rvalue of type ‘Specification<Issue>’
  PrioritySpecification priority_spec(Issue::Priority::High);
  auto spec = AssigneeSpecification("Jonasz") &&
              const_cast<PrioritySpecification&>(priority_spec);

  auto filtered_by_assignee_and_priority = m_filter.filter(issues, spec);

  expectIssueKeys(filtered_by_assignee_and_priority, {"ISS4", "ISS5"});
}

TEST_F(SpecificationFixture, TestSharedPtr) {
  std::shared_ptr<Specification<Issue>> assignee_spec =
      std::make_shared<AssigneeSpecification>("Jonasz");
  std::shared_ptr<Specification<Issue>> prio_spec =
      std::make_shared<PrioritySpecification>(Issue::Priority::High);
  auto spec = *assignee_spec && *prio_spec;
  auto filtered_by_assignee_and_priority = m_filter.filter(issues, spec);

  expectIssueKeys(filtered_by_assignee_and_priority, {"ISS4", "ISS5"});
}
