#ifndef _RAY_H_
#define _RAY_H_

#include "Matrix.h"
#include <stdint.h>

class RayColor {
public:
  uint8_t red, green, blue;
  RayColor() : red(0), green(0), blue(0) {}
  RayColor(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b) {}
  ~RayColor() {}
};

class Ray {
  
private:
  Matrix position;
  Matrix direction;

};

#endif /* _RAY_H_ */
