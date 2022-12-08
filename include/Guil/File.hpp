#pragma once
#include <Guil/Unix.hpp>
#include <string>
#include <vector>

namespace guil {
namespace filesystem {
enum Mode {
  ReadOnly = 00,
  WriteOnly = 01,
  ReadWrite = 02,
  Syncronize = 04010000,
  Create = 0100
};

class File {
private:
  int Mode;

public:
  int Fd;
  struct stat Stat;
  std::string Path;

  File(std::string Path, int mode);
  ~File();

  void Close();
  void Sync();
  void TakeOwn();
  void ReloadMetadata();

  int Read(std::vector<char> &Buffer);
  int Write(const std::string &Data);
};
} // namespace filesystem
} // namespace guil