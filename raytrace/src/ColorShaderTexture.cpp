#include "ColorShaderTexture.h"

RTMaterial ColorShaderTexture::shade(float u, float v, RTMaterial m) {
  RTColor color = texture.get(u, v);
  m.setDiffColor(color);
  return m;
}
