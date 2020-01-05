#include "Block.h"

namespace sun
{

void Block::Set(const uint8_t *a)
{
  while (!IsFull())
    b_.a[i_++] = *a++;
}

void Block::Set(uint8_t v)
{
  if (IsFull())
    i_ = 0;
  b_.a[i_++] = v;
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
