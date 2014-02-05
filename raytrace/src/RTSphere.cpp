#include "RTSphere.h"

RTSphere::RTSphere(Matrix origin, float radius) {
  _origin = origin;
  _radius = radius;
}

// http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
MatrixPtr RTSphere::intersect(const Ray &ray) {


  Matrix x0 = _origin;
  Matrix x1 = ray.getOrigin();
  Matrix x2 = ray.getOrigin() + ray.getDirection();

  float d = ((x2 - x1).crossProduct(x1 - x0)).length() / ((x2-x1).length());
  if (_radius >= d) {
    return MatrixPtr(new Matrix());
  } else {
    return MatrixPtr(NULL);
  }

}
