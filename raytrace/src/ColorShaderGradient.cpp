#include "ColorShaderGradient.h"

RTMaterial ColorShaderGradient::shade(float u, float v, RTMaterial m) {



  m.setDiffColor(RTColor(v,0,0));
  
  return m;

}
