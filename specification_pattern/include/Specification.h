#pragma once

// Forward declaration
template <typename T>
class AndSpecification;

template <typename T>
class Specification {
 public:
  virtual ~Specification() = default;
  virtual bool is_satisfied(T& item) = 0;

  AndSpecification<T> operator&&(Specification<T>& other) {
    return AndSpecification<T>(*this, other);
  }
};