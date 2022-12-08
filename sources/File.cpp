#include <Guil/File.hpp>
#include <Guil/Unix.hpp>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

#ifndef GUIL_NO_CATCH
#define Catch                                                                  \
  if (errno != 0) {                                                            \
    throw std::runtime_error(strerror(errno));                                 \
  }
#else
#define Catch
#endif

using namespace guil::filesystem;

File::File(std::string Path, int mode) {
  this->Fd = open(Path.c_str(), mode);
  this->Path = Path;
  this->Mode = mode;

  Catch;

  this->ReloadMetadata();
}

File::~File() { Close(); }

void File::TakeOwn() {
  chmod(this->Path.c_str(), 0666);
  Catch;
}

void File::ReloadMetadata() {
  stat(Path.c_str(), &this->Stat);
  Catch;
}

int File::Write(const std::string &Data) {
  const char *Payload = Data.c_str();

  int Wrote = write(this->Fd, Payload, Data.size());

  Catch;

  this->ReloadMetadata();

  return Wrote;
}

int File::Read(std::vector<char> &Buffer) {
  char *CBuffer = new char[Buffer.capacity()];
  int Read = read(this->Fd, CBuffer, Buffer.capacity());

  for (int Here = 0; Here < Read; ++Here) {
    Buffer.push_back(CBuffer[Here]);
  }

  delete[] CBuffer;

  Catch;
  this->ReloadMetadata();

  return Read;
}

void File::Sync() {
  fsync(this->Fd);
  Catch;

  this->Close();

  Catch;
  this->Fd = open(this->Path.c_str(), this->Mode);

  Catch;

  this->ReloadMetadata();
}

void File::Close() {
  close(this->Fd);

  Catch;
}