#pragma once

#include <string>

class Issue {
 public:
  enum class Type { Story, Task, Bug };
  enum class Priority { Highest, High, Medium, Low, Lowest };

  Issue(std::string_view key, std::string_view reporter,
        std::string_view assignee, Type type, Priority priority)
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
