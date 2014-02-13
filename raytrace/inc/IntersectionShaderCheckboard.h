#ifndef _INTERSECTIONSHADERCHECKERBOARD_H_
#define _INTERSECTIONSHADERCHECKERBOARD_H_

#include "IntersectionShader.h"

class IntersectionShaderCheckerboard : public IntersectionShader {

public:
  IntersectionShaderCheckerboard(int m, int n) : _m(m), _n(n) {}
  
  virtual bool shade(float u, float v) {

    if (((int)(u * _m) % 2) == 0) {
      if (((int)(v * _n) % 2) == 0) {
        return true;
      } else {
        return false;
      }
    } else {
      if (((int)(v * _n) % 2) == 0) {
        return false;
      } else {
        return true;
      }
    }

  }

private:
  int _m, _n;


};

#endif /* _INTERSECTIONSHADERCHECKERBOARD_H_ */
