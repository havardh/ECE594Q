#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vector.h"

class Camera {

public:
  Camera() {}

  Camera(Vector pos, Vector dir, float focalDistance, Vector up, float fov) {
    E = pos;
    V = dir;
    (void) focalDistance;
    U = up;
    phi = fov;
  }

  const Vector& getPosition() const { return E; }
  const Vector& getDirection() const { return V; }
  const Vector& getUp() const { return U; }
  float getFieldOfView() const { return phi; }

  void setPosition(const Vector position) { E = position; }
  void setDirection(const Vector direction) { V = direction; }
  void setUp(const Vector up) { U = up; }

private:
  Vector E; // Position
  Vector V; // Direction
  Vector U; // Up vector
  float phi; // vertical field of view

};


#endif /* _CAMERA_H_ */
