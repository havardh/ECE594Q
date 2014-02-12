#ifndef _COLORSHADER_H_
#define _COLORSHADER_H_

#include "RTMaterial.h"

class ColorShader {

public:
  virtual RTMaterial shade(float, float, RTMaterial) = 0;

};

#endif /* _COLORSHADER_H_ */
