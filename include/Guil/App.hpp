#pragma once
#include <exception>
#include <iostream>
#include <string>
#include <vector>

namespace guil {
class App {
public:
  std::vector<std::string> Args;

  int Start();
};
} // namespace guil

int main(int argc, char **argv);