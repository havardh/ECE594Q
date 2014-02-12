#include "ColorShaderCheckerboard.h"

RTMaterial ColorShaderCheckerboard::shade(float u, float v, RTMaterial m) {

  if (((int)(u * _m) % 2) == 0) {
    if (((int)(v * _n) % 2) == 0) {
      m.setDiffColor(RTColor::BLACK);
    } else {
      m.setDiffColor(RTColor::WHITE);
    }
  } else {
    if (((int)(v * _n) % 2) == 0) {
      m.setDiffColor(RTColor::WHITE);
    } else {
      m.setDiffColor(RTColor::BLACK);
    }
  }
  return m;
}
