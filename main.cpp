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
  Vector< int > v(size, 0);
  return v.getSize() == size;
}

bool test4()
{
  using topit::Vector;
  constexpr size_t size = 3ull;
  Vector< int > v(size, 1);
  try {
    int value = v.at(0);
    return value == 1;
  }
  catch (...) {
    return false;
  }
}

bool test5()
{
  using topit::Vector;
  constexpr size_t size = 3ull;
  Vector< int > v(size, 0);
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

bool test6()
{
  using topit::Vector;
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 1);
  try {
    int value = v.at(0);
    return value == 1;
  }
  catch (...) {
    return false;
  }
}

bool test7()
{
  using topit::Vector;
  constexpr size_t size = 3ull;
  const Vector< int > v(size, 0);
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
    { test5, "Out of range access generates exceptions" },
    { test6, "const: In range access does not generate exceptions" },
    { test7, "const: Out of range access generates exceptions" }

  };
  size_t count = sizeof(tests) / sizeof(case_t);
  std::cout << std::boolalpha;
  bool result = true;
  size_t successes = 0, fails = 0;
  for (size_t i = 0; i < count; ++i) {
    bool case_result = tests[i].first();
    successes += case_result;
    fails += !case_result;
    result = result && case_result;
    std::cout << case_result;
    std::cout << ": ";
    std::cout << tests[i].second << "\n";
  }
  std::cout << 'SUMMARY\n';
  std::cout << result << ": TEST RESULTS\n";
  std::cout << fails << ":failed tests\n";
  std::cout << successes << ":passed tests\n";
}
