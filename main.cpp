#include <iostream> 
#include "vector-top-it.hpp"
#include <cstddef>

bool test1()
{
  using topit::Vector;
  Vector< int > v;
  return v.isEmpty();
}

bool test2()
{
  using topit::Vector;
  Vector< int > v;
  return v.getSize();
}

bool test3()
{
  using topit::Vector;
  constexpr size_t size = 3ull;
  Vector< int > v(size);
  return v.getSize() == size;
}

bool test4()
{
  using topit::Vector;
  constexpr size_t size = 3ull;
  Vector< int > v(size);
  try {
    v.at(0);
    return true;
  }
  catch (...) {
    return false;
  }
}

bool test5()
{
  using topit::Vector;
  constexpr size_t size = 3ull;
  Vector< int > v(size);
  try {
    v.at(size + 1);
    return false;
  }
  catch (const std::output_of_range&) {
    return true;
  }
  catch (...) {
    return false;
  }
}

int main()
{
  using test_t = bool(*)();
  using case_t = std::pair<test_t, const char* >;
  case_t tests[] = {
    { test1, "Default constracted vector is empty" },
    { test2, "Default constracted vector size is zero" },
    { test3, "Vector constracted with size has non-zero size" },
    { test4, "In range access does not generate exceptions" },
    { test5, "Out of range access generates exceptions" }

  };
  size_t count = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;
  for (size_t i = 0; i < count; ++i) {
    std::cout << tests[i].first();
    std::cout << ": ";
    std::cout << tests[i].second << "\n";
  }
}
