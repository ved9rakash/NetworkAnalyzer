#include "fibonacci.h"
#include <iostream>

template <typename T> auto test(T x) {
  int y{5};
  return x + y;
}
int main() {
  std::cout << "Fibonacci of 5 is: " << fibonacci(5);
}