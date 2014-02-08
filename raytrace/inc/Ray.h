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

public:
 Ray() : _origin(0,0,0), _direction(0,0,0) {}
  Ray(const Matrix &origin, const Matrix &direction) {
    _origin = origin;
    _direction = direction;
  }

  void print() const {
    _origin.printPoint();
    _direction.printPoint();
  }

  const Matrix getOrigin() const { return _origin; }
  const Matrix getDirection() const { return _direction; }

private:
  Matrix _origin;
  Matrix _direction;

};

#endif /* _RAY_H_ */
