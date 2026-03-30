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
  catch (const std::out_of_range&) {
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
  catch (const std::out_of_range&) {
    return true;
  }
  catch (...) {
    return false;
  }
}

bool test8()
{
  using topit::Vector;
  const Vector< int > v(2, 0);
  Vector< int > yav = v; //конструктор копирования auto & yav = v; указание компилятору что нужен типа но связать по ссылке и будет просто ссылка на тот же самый вектор и сравнение одних и тех же векторов.
  return yav == v;
}

bool test9()
{
  using topit::Vector;
  Vector< int > v;
  Vector< int > yav(2, 0);
  bool res = v != yav;
  v = yav; //конструктор присваивания
  return res && v == yav;
}

bool test10()
{
  using topit::Vector;
  Vector< int > v(2, 0);
  Vector< int > yav(3, 1);
  Vector< int > cpy_v(v);
  Vector< int > cpy_yav(yav);
  v.swap(yav);
  return cpy_v == yav && cpy_yav == v;
}

bool test11()
{
  using topit::Vector;
  Vector< int > v(2, 0);
  Vector< int > cpy_v(v);
  Vector< int > yav = std::move(v);
  return yav == cpy_v;
}

bool test12()
{
  using topit::Vector;
  Vector< int > v(2, 0);
  Vector< int > cpy(v);
  Vector< int > yav;
  yav == std::move(v);
  return yav == cpy;
}
// вааай, доделай тесты для домашка getCapacity, != == []

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
    { test7, "const: Out of range access generates exceptions" },
    { test8, "copy constructor" },
    { test9, "copy assigment operator" },
    { test10, "swap for two vectors" },
    { test11, "Move constructor" },
    { test12, "Move assigment operator" }

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
  std::cout << "SUMMARY\n";
  std::cout << result << ": TEST RESULTS\n";
  std::cout << fails << ":failed tests\n";
  std::cout << successes << ":passed tests\n";
}
