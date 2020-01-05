#include <string.h>

#include "Tea.h"
#include "Rand.h"
#include "Block.h"
#include "TeaCore.h"

namespace sun
{

Tea::Tea()
{
  *this = Tea("KEY NOT SET!");
}

Tea::Tea(const char *key)
{
  int i,n;
  for (i=0,n=strlen(key); i<n; ++i) {
    if (i<n)
      key_.emplace_back(key[i]);
    else
      key_.emplace_back(0);
  }
}

Tea::Tea(Tea&& t)
{
  key_.swap(t.key_);
}

Tea& Tea::operator=(Tea&& t)
{
  key_.swap(t.key_);
  return *this;
}

Tea& Tea::SetKey(const std::string& key)
{
  *this = Tea(key.c_str());
  return *this;
}

Tea& Tea::SetKey(const char key[kKeySize])
{
  SetKey(std::string(key, kKeySize));
  return *this;
}

const uint32_t *Tea::GetKey()
{
  return (const uint32_t *)key_.data();
}

static Rand rand;

Tea::output_t Tea::Encrypt(input_t in)
{
  output_t out;
  Block b1,b2,plain,cipher;
  uint8_t *ip,*op;
  int i,pad;
  pad=(-in.size()-2)%Block::kBlockSize;
  if (pad<0)
    pad+=8;
  const int k1=1+pad+2;
  const int k2=k1+in.size();
  const int n=k2+7;
  out.resize(n);
  ip=in.data(), op=out.data();
  plain.Set((rand.GetChar()&0xf8)|pad);
  for (i=1; i<n; ++i) {
    if (i<k1)
      plain.Set(rand.GetChar());
    else if (i<k2)
      plain.Set(*ip++);
    else
      plain.Set((uint8_t)0);
    plain.Xor(b1);
    TeaCore::Encrypt(
        (const uint32_t *)plain.Get(),
        (uint32_t *)cipher.Get(),
        GetKey());
    cipher.Xor(b2);
    b1=cipher;
    b2=plain;
  }
  return out;
}

Tea::output_t Tea::Decrypt(input_t in)
{
  output_t out;
  Block t1,t2,b1,b2,plain,cipher;
  uint8_t *ip,*op;
  const uint8_t *p;
  int i,j,pad,k1,k2,n;
  n=in.size();
  if (n%8 || n<16)
    goto end;
  ip=in.data();
  for (i=1; i<n; ++i) {
    cipher.Set(*ip++);
    if (plain.IsFull()) {
      t1=cipher;
      cipher.Xor(b2);
      TeaCore::Decrypt(
          (const uint32_t *)cipher.Get(),
          (uint32_t *)plain.Get(),
          GetKey());
      t2=plain;
      plain.Xor(b1);
      b1=t1;
      b2=t2;
      p=plain.Get();
      for (j=i-8; j<i; ++i) {
        if (!j) {
          pad=*p++&(Block::kBlockSize-1);
          k1=1+pad+2;
          out.resize(n-k1-7);
          op=out.data();
          k2=k1+out.size();
        }
        else if (j<k1) {
          ++p;
        }
        else if (j<k2) {
          *op++=*p++;
        }
        else {
          goto end;
        }
      }
    }
  }
end:
  return out;
}

}
