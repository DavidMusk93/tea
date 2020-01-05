#pragma once

#include <stdint.h>

#include <vector>
#include <string>

namespace sun
{

class Tea
{
 public:
  using input_t = std::vector<uint8_t>;
  using output_t = input_t;

  static constexpr int kKeySize = 16;

 public:
  Tea();
  Tea(const char *key);
  Tea(Tea&& t);
  Tea& operator=(Tea&& t);
  Tea& SetKey(const std::string& key);
  Tea& SetKey(const char key[kKeySize]);
  const uint32_t *GetKey();
  output_t Encrypt(input_t in);
  output_t Decrypt(input_t in);

 private:
  std::vector<uint8_t> key_;
};

}
