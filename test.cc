#include <stdio.h>

#include "Tea.h"

int main()
{
  sun::Tea tea("a4s3d2f1");
  std::vector<uint8_t> in = {0x1, 0x2, 0x3, 0x4, 0x11, 0x22, 0x33, 0x44, 0x5, 0x6, 0x7, 0x8, 0x55, 0x66, 0x77, 0x88, 0x9};
  auto out1 = tea.Encrypt(in);
  auto out2 = tea.Decrypt(out1);
  uint8_t *ip = in.data();
  bool b = true;
  for (auto i: out2) {
    if (*ip++ != i) {
      b = false;
      break;
    }
  }
  puts(b?"pass":"failure");
  return 0;
}
