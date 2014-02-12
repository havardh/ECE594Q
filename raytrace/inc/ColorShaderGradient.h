#ifndef _COLORSHADERGRADIENT_H_
#define _COLORSHADERGRADIENT_H_

#include "ColorShader.h"

class ColorShaderGradient : public ColorShader {

public:
  virtual RTMaterial shade(float u, float v, RTMaterial m);

};

#endif /* _COLORSHADERGRADIENT_H_ */
