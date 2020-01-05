#pragma once

namespace sun
{

class Rand
{
 private:
  void Open();
  void BlockRead();

 public:
  Rand(bool do_open=false);
  ~Rand();
  char GetChar();

 private:
  int fd_;
  int i_;
  char buf_[1024];

  static constexpr int kBufferSize = sizeof(buf_);
  static constexpr const char *kEntropySource = "/dev/urandom";
};

}
