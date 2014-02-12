#ifndef _COLORSHADERCHECKERBOARD_H_
#define _COLORSHADERCHECKERBOARD_H_

#include "ColorShader.h"

class ColorShaderCheckerboard : public ColorShader {

public:
  ColorShaderCheckerboard(int m, int n) : _m(m), _n(n) {}
  virtual RTMaterial shade(float u, float v, RTMaterial m);

private:
  int _m, _n;

};

#endif /* _COLORSHADERCHECKERBOARD_H_ */
