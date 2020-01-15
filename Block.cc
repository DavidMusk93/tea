#include "Block.h"

namespace sun
{

void Block::Set(const uint8_t *a)
{
  i_=0;
  b_.n=*(uint64_t *)a;
  i_=kBlockSize;
}

void Block::Set(uint8_t v)
{
  if (IsFull())
    i_ = 0;
  b_.a[i_++] = v;
}

void Block::Xor(const Block& b)
{
  b_.n ^= (uint64_t)b;
}

const uint8_t *Block::Get()
{
  return const_cast<const uint8_t *>(b_.a);
}

bool Block::IsFull()
{
  return i_ == kBlockSize;
}

Block::operator uint64_t() const
{
  return b_.n;
}

}
