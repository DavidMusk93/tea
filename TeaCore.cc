#include "TeaCore.h"

namespace sun
{

void TeaCore::Encrypt(const uint32_t *in, uint32_t *out, const uint32_t *key)
{
  uint32_t v0,v1,k0,k1,k2,k3,i,sum;
  v0=in[0], v1=in[1];
  k0=key[0], k1=key[1], k2=key[2], k3=key[3];
  for (i=0, sum=0; i<COUNT; ++i) {
    sum+=DELTA;
    v0+=((v1<<4)+k0)^(v1+sum)^((v1>>5)+k1);
    v1+=((v0<<4)+k2)^(v0+sum)^((v0>>5)+k3);
  }
  out[0]=v0, out[1]=v1;
}

void TeaCore::Decrypt(const uint32_t *in, uint32_t *out, const uint32_t *key)
{
  uint32_t v0,v1,k0,k1,k2,k3,i,sum;
  v0=in[0], v1=in[1];
  k0=key[0], k1=key[1], k2=key[2], k3=key[3];
  for (i=0, sum=DELTA<<4; i<COUNT; ++i) {
    v1-=((v0<<4)+k2)^(v0+sum)^((v0>>5)+k3);
    v0-=((v1<<4)+k0)^(v1+sum)^((v1>>5)+k1);
    sum-=DELTA;
  }
  out[0]=v0, out[1]=v1;
}

}
