#include <iostream>
#include <vector>

class Issue {
   public:
    enum class Type { Story, Task, Bug };
    enum class Priority { Highest, High, Medium, Low, Lowest };

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

class IssueFilter {
   public:
    std::vector<Issue> by_assignee(std::vector<Issue> issues,
                                   std::string assignee) {
        std::vector<Issue> filtered_issues;

        for (auto issue : issues) {
            if (issue.getAssignee() == assignee)
                filtered_issues.push_back(issue);
        }
        return filtered_issues;
    }

    std::vector<Issue> by_reporter(std::vector<Issue> issues,
                                   std::string reporter) {
        std::vector<Issue> filtered_issues;

        for (auto issue : issues) {
            if (issue.getReporter() == reporter)
                filtered_issues.push_back(issue);
        }
        return filtered_issues;
    }
};

int main(int argc, char* argv[]) {
    std::vector<Issue> issues = {
        {"ISS1", "Marcin", "Tomasz", Issue::Type::Bug, Issue::Priority::Medium},
        {"ISS2", "Marcin", "Mariusz", Issue::Type::Story,
         Issue::Priority::Medium},
        {"ISS3", "Robert", "Mariusz", Issue::Type::Task, Issue::Priority::High},
    };

    IssueFilter filter;
    auto filtered_by_assignee = filter.by_assignee(issues, "Mariusz");

    for (auto& issue : filtered_by_assignee) {
        std::cout << issue.getKey() << std::endl;
    }

    auto filtered_by_reporter = filter.by_reporter(issues, "Marcin");

    for (auto& issue : filtered_by_reporter) {
        std::cout << issue.getKey() << std::endl;
    }

    return 0;
}
