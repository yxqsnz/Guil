#include <Guil/App.hpp>

int main(int argc, char **argv) {
  guil::App app;

  for (int i = 0; i < argc; ++i) {
    app.Args.push_back(std::string(argv[i]));
  }

  try {
    return app.Start();
  } catch (std::exception &e) {
    std::cerr << e.what();
    return 1;
  }
}
