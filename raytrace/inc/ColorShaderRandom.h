#ifndef _COLORSHADERRANDOM_H_
#define _COLORSHADERRANDOM_H_

#include "RTMaterial.h"
#include "ColorShader.h"
#include <stdlib.h>

static float r() {
  return rand() / (float) RAND_MAX;
}

class ColorShaderRandom : public ColorShader {

public: 
  virtual RTMaterial shade(float u, float v, RTMaterial m) {
    m.setDiffColor(RTColor(r(), r(), r()));
    m.setKTransparency(r());
    return m;
  }

};

#endif /* _COLORSHADERRANDOM_H_ */
