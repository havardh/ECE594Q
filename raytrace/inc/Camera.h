#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Matrix.h"

class Camera {

public:
  Camera() {}

  Camera(Matrix pos, Matrix dir, float focalDistance, Matrix up, float fov) {
    E = pos;
    V = dir;
    (void) focalDistance;
    U = up;
    phi = fov;
  }

  const Matrix& getPosition() const { return E; }
  const Matrix& getDirection() const { return V; }
  const Matrix& getUp() const { return U; }
  float getFieldOfView() const { return phi; }

  void setPosition(const Matrix position) { E = position; }
  void setDirection(const Matrix direction) { V = direction; }
  void setUp(const Matrix up) { U = up; }

private:
  Matrix E; // Position
  Matrix V; // Direction
  Matrix U; // Up vector
  float phi; // vertical field of view

};


#endif /* _CAMERA_H_ */
