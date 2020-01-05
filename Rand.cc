#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "Rand.h"

namespace sun
{

void Rand::Open()
{
  fd_ = open(kEntropySource, O_RDONLY);
  if (fd_ < 0)
    perror("Open entropy source failed");
}

void Rand::BlockRead()
{
  if (fd_ < 0)
    Open();
  if (i_ == kBufferSize) {
    i_ = 0;
    (void)read(fd_, buf_, kBufferSize);
  }
}

Rand::Rand(bool do_open): fd_(-1), i_(kBufferSize)
{
  if (do_open)
    Open();
}

Rand::~Rand()
{
  if (fd_ > 0)
    close(fd_);
}

char Rand::GetChar()
{
  BlockRead();
  return buf_[i_++];
}

}
