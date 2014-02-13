#ifndef _INTERSECTIONSHADERCOLOR_H_
#define _INTERSECTIONSHADERCOLOR_H_

#include "IntersectionShader.h"

class IntersectionShaderColor : public IntersectionShader {
  
  virtual bool shade(float u, float v, RTMaterial m) {
    
    
    return true;

    RTColor cutoff(0.5, 0.5, 0.5);

    if ( !(m.getDiffColor() < 0.5)) {
      return true;
      return false;
    }
    return true;
  }

};

#endif /* _INTERSECTIONSHADERCOLOR_H_ */
