#pragma once

#include "Specification.h"

template <typename T>
class AndSpecification : public Specification<T> {
 private:
  Specification<T>& first_;
  Specification<T>& second_;

 public:
  explicit AndSpecification(Specification<T>& first, Specification<T>& second)
      : first_(first), second_(second) {}

  bool is_satisfied(T& item) override {
    return first_.is_satisfied(item) && second_.is_satisfied(item);
  }
};
