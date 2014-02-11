#ifndef _INTERSECTIONSHADERVISIBLE_H_
#define _INTERSECTIONSHADERVISIBLE_H_

#include "IntersectionShader.h"

class IntersectionShaderVisible {

public:
  virtual bool shade(float u, float v) {
    if ( u >= 0 && v >= 0 && u <= 1.0 && v <= 1.0) {
      return 1;
    }

    return 0;
  }

};

#endif /* _INTERSECTIONSHADERVISIBLE_H_ */
