#ifndef _INTERSECTIONSHADER_H_
#define _INTERSECTIONSHADER_H_

#include "RTMaterial.h"

class IntersectionShader {

public:
  virtual bool shade(float u, float v, RTMaterial m) = 0;
};

#endif /* _INTERSECTIONSHADER_H_ */
