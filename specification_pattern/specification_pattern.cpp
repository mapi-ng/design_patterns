/**
 * @author Marcin Pilch
 */
#include <iostream>
#include <vector>
#include <memory>

class Issue {
 public:
  enum class Type {
    Story,
    Task,
    Bug
  };

  enum class Priority {
    Highest,
    High,
    Medium,
    Low,
    Lowest
  };

  Issue(std::string key, std::string reporter, std::string assignee,
        Type type, Priority priority)
      : key_(key),
        reporter_(reporter),
        assignee_(assignee),
        type_(type),
        priority_(priority) {}

  std::string getKey() const { return key_; }
  std::string getReporter() const { return reporter_; }
  std::string getAssignee() const { return assignee_; }
  Type getType() const { return type_; }
  Priority getPriority() const { return priority_; }

 private:
  std::string key_;
  std::string reporter_;
  std::string assignee_;
  Type type_;
  Priority priority_;
};

// Forward declaration
template <typename T>
class AndSpecification;

template <typename T>
class Specification {
 public:
  virtual bool is_satisfied(T& item) = 0;

  AndSpecification<T> operator&&(Specification<T>& other) {
    return AndSpecification<T>(*this, other);
  }
};

template <typename T>
class AndSpecification : public Specification<T> {
 private:
  Specification<T>& first_;
  Specification<T>& second_;

 public:
  explicit AndSpecification(Specification<T>& first, Specification<T>& second) : first_(first), second_(second) {}

  bool is_satisfied(T& item) override {
    return first_.is_satisfied(item) && second_.is_satisfied(item);
  }
};

class AssigneeSpecification : public Specification<Issue> {
 private:
  std::string assignee_;

 public:
  explicit AssigneeSpecification(std::string assignee) : assignee_(assignee) {}

  bool is_satisfied(Issue& issue) override {
    return issue.getAssignee() == assignee_;
  }
};

class ReporterSpecification : public Specification<Issue> {
 private:
  std::string reporter_;

 public:
  explicit ReporterSpecification(std::string reporter) : reporter_(reporter) {}

  bool is_satisfied(Issue& issue) override {
    return issue.getReporter() == reporter_;
  }
};

class PrioritySpecification : public Specification<Issue> {
 private:
  Issue::Priority priority_;

 public:
  explicit PrioritySpecification(Issue::Priority priority) : priority_(priority) {}

  bool is_satisfied(Issue& issue) override {
    return issue.getPriority() == priority_;
  }
};

class PriorityNotSpecification : public Specification<Issue> {
 private:
  Issue::Priority priority_;

 public:
  PriorityNotSpecification(Issue::Priority priority) : priority_(priority) {}

  bool is_satisfied(Issue& issue) override {
    return issue.getPriority() != priority_;
  }
};

template <typename T>
class Filter {
 public:
  virtual std::vector<T> filter(std::vector<T> items,
                                Specification<T>& specification) = 0;
};

class IssueFilter : public Filter<Issue> {
 public:
  std::vector<Issue> filter(std::vector<Issue> issues,
                            Specification<Issue>& specification) override {
    std::vector<Issue> filtered_issues;

    for (auto& issue : issues) {
      if (specification.is_satisfied(issue))
        filtered_issues.push_back(issue);
    }

    return filtered_issues;
  }
};

int main(int argc, char* argv[]) {
  std::vector<Issue> issues = {
      {"ISS1", "Marcin", "Tomasz", Issue::Type::Bug, Issue::Priority::Low},
      {"ISS2", "Marcin", "Mariusz", Issue::Type::Story,
       Issue::Priority::Medium},
      {"ISS3", "Robert", "Mariusz", Issue::Type::Task, Issue::Priority::High},
      {"ISS4", "Mariusz", "Jonasz", Issue::Type::Task, Issue::Priority::High},
      {"ISS5", "Marcin", "Jonasz", Issue::Type::Task, Issue::Priority::High},
      {"ISS5", "Marcin", "Jonasz", Issue::Type::Task, Issue::Priority::Low},
  };

  IssueFilter filter;
  AssigneeSpecification spec_by_assignee("Mariusz");
  ReporterSpecification spec_by_reporter("Marcin");
  PrioritySpecification spec_by_priority(Issue::Priority::High);
  PriorityNotSpecification spec_by_priority_not(Issue::Priority::Medium);
  AndSpecification<Issue> spec_priority_and_reporter(spec_by_reporter, spec_by_priority);

  auto filtered_by_assignee = filter.filter(issues, spec_by_assignee);

  std::cout << "Issues with assignee Mariusz: \n";
  for (auto& issue : filtered_by_assignee) {
    std::cout << issue.getKey() << std::endl;
  }

  auto filtered_by_reporter = filter.filter(issues, spec_by_reporter);

  std::cout << "Issues with reporter Marcin: \n";
  for (auto& issue : filtered_by_reporter) {
    std::cout << issue.getKey() << std::endl;
  }

  auto filtered_by_priority = filter.filter(issues, spec_by_priority);

  std::cout << "Issues with priority High: \n";
  for (auto& issue : filtered_by_priority) {
    std::cout << issue.getKey() << std::endl;
  }

  auto filtered_by_priority_not = filter.filter(issues, spec_by_priority_not);

  std::cout << "Issues with priority NOT Medium: \n";
  for (auto& issue : filtered_by_priority_not) {
    std::cout << issue.getKey() << std::endl;
  }

  auto filtered_by_priority_and_reporter = filter.filter(issues, spec_priority_and_reporter);

  std::cout << "Issues with priority High and reporter Marcin: \n";
  for (auto& issue : filtered_by_priority_and_reporter) {
    std::cout << issue.getKey() << std::endl;
  }

  /* Leads to segmentation fault (references to non-existing objects within AndSpecification)
  auto spec = AssigneeSpecification("Jonasz") && PrioritySpecification(Issue::Priority::High);
  */

  std::shared_ptr<Specification<Issue>> assignee_spec = std::make_shared<AssigneeSpecification>("Jonasz");
  std::shared_ptr<Specification<Issue>> prio_spec = std::make_shared<PrioritySpecification>(Issue::Priority::High);
  auto spec = *assignee_spec && *prio_spec;
  auto filtered_by_priority_and_reporter_operator = filter.filter(issues, spec);

  std::cout << "Issues with priority High and assignee Jonasz: \n";
  for (auto& issue : filtered_by_priority_and_reporter_operator) {
    std::cout << issue.getKey() << std::endl;
  }

  return 0;
}
