#pragma once

#include <stdint.h>

namespace sun
{

class Block
{
 public:
  static constexpr const int kBlockSize = 8;

 public:
  void Set(const uint8_t *a);
  void Set(uint8_t v);

  void Xor(const Block& b);
  const uint8_t *Get();
  bool IsFull();

  operator uint64_t() const;

 private:
  using block_t = union { uint64_t n; uint8_t a[kBlockSize]; };
  block_t b_{0};
  int i_{0};
};

}
