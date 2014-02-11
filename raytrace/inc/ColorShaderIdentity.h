#ifndef _COLORSHADERIDENTITY_H_
#define _COLORSHADERIDENTITY_H_

#include "RTMaterial.h"
#include "ColorShader.h"

class ColorShaderIdentity : public ColorShader {

public: 
  virtual RTMaterial shade(float u, float v, RTMaterial m) {
    return m;
  }

};

#endif /* _COLORSHADERIDENTITY_H_ */
