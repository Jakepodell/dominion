#pragma once
#include <iostream>

namespace typeplay {
template <typename... Ts> void print(const Ts &...args) {
  (std::cout << ... << args) << std::endl;
}

template <> void print<int>(const int &arg) {
  std::cout << "Integer value: " << arg << std::endl;
}
} // namespace typeplay