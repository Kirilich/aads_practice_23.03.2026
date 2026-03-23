#include <iostream> 
#include "vector-top-it.hpp"
#include <cstddef>

bool test1()
{
  using topit::Vector;
  Vector< int > v;
  return v.isEmpty();
}

int main()
{
  using test_t = bool(*)();
  using case_t = std::pair<test_t, const char* >;
  case_t tests[] = {
    { test1, "Default constracted vector must be empty" }
  };
  size_t count = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < count; ++i) {
    std::cout << tests[i].first();
    std::cout << ": ";
    std::cout << tests[i].second << "\n";
  }
}
