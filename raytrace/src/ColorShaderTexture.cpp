#include "ColorShaderTexture.h"

RTMaterial ColorShaderTexture::shade(float u, float v, RTMaterial m) {
  printf("%f %f\n", u,v);
  RTColor color = texture.get(u, v);
  m.setDiffColor(color);
}
