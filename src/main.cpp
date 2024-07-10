#include "fibonacci.h"
#include <iostream>

template <typename T> auto test(T x) {
  return x;
}
int main() {
  std::cout << "Fibonacci of 5 is: " << fibonacci(5);
}