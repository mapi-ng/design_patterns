#pragma once
#include "Specification.h"

template <typename T>
class Filter {
 public:
  virtual std::vector<T> filter(std::vector<T> items,
                                Specification<T>& specification) = 0;
};
