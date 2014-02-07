#include "RTSphere.h"

#define EPSILON 0.000001

RTSphere::RTSphere(Matrix origin, float radius) {
  _origin = origin;
  _radius = radius;
}

IntersectionPtr RTSphere::getIntersection(const Ray &ray) {

  Matrix O = ray.getOrigin();
  Matrix L = ray.getDirection();
  Matrix C = this->_origin;
  float  r = this->_radius;

  Matrix O_C = O-C;
  
  float a = -(L.dot(O_C));
  float b = (L.dot(O_C) * L.dot(O_C)) - (O_C).dot(O_C) + (r*r);

  if (b < 0) {
    return IntersectionPtr(NULL);
  } else {
    float d = a - (float)sqrt(b);
    //DPRINTF("..\n");
    IntersectionPtr intersection(new Intersection(this, ray, Matrix(O + d * L)));
    return intersection;
  }
}

// http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
IntersectionPtr RTSphere::intersect(const Ray ray) {

  Matrix x0 = _origin;
  Matrix x1 = ray.getOrigin();
  Matrix x2 = ray.getOrigin() + ray.getDirection();


  if ((x1 - x0).length() < (x2 - x0).length()) {
    return IntersectionPtr(NULL);
  }

  float d = ((x2 - x1).crossProduct(x1 - x0)).length() / ((x2-x1).length());

  if (_radius >= d) {
    return getIntersection(ray);
  } else {
    return IntersectionPtr(NULL);
  }
  
}

MatrixPtr RTSphere::normal(const Matrix &point, const Matrix &from) {


  Matrix direction;
  if ((from - _origin).length() > _radius) {
    direction = (point - _origin);
  } else {
    direction = (_origin - point);
  }
  return MatrixPtr(new Matrix(direction.normalize()));

}
