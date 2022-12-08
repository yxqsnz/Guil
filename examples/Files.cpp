#include <Guil/App.hpp>
#include <Guil/File.hpp>
#include <iostream>
#include <vector>

using namespace guil;
using namespace filesystem;

int App::Start() {
  File morning("./gm.txt", Create | ReadWrite | Syncronize);

  morning.TakeOwn();

  std::cout << "Fd    : " << morning.Fd << "\n";
  int Wrote = morning.Write("Good morning. are you good?");

  std::cout << "Wrote : " << Wrote << "\n";

  morning.Sync();

  std::vector<char> Buffer(27);

  int Read = morning.Read(Buffer);

  std::cout << "Count : " << Read << "\n";

  std::cout << "Read  : ";

  for (char c : Buffer) {
    std::cout << c;
  }

  std::cout << "\n";

  return 0;
}
