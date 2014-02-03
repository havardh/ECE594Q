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

  const Matrix& getPosition() { return E; }
  const Matrix& getDirection() { return V; }
  const Matrix& getUp() { return U; }
  float getFieldOfView() { return phi; }

private:
  Matrix E; // Position
  Matrix V; // Direction
  Matrix U; // Up vector
  float phi; // vertical field of view

};


#endif /* _CAMERA_H_ */
