#pragma once

#include <stdint.h>

namespace sun
{

class TeaCore
{
 private:
  static constexpr uint32_t DELTA = 0x9e3779b9;
  static constexpr uint32_t COUNT = 16;

 public:
  static void Encrypt(const uint32_t *in, uint32_t *out, const uint32_t *key);
  static void Decrypt(const uint32_t *in, uint32_t *out, const uint32_t *key);
};

}
