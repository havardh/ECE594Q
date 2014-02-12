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

    Matrix p(O + d * L);

    if (fabs ((ray.getOrigin() - p).length()) > 0.001) {
      return IntersectionPtr(new Intersection(this, ray, p));
    } else {
      return IntersectionPtr(NULL);
    }
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
  (void) from;

  Matrix direction = point - _origin;
  return MatrixPtr(new Matrix(direction.normalize()));

}

RTMaterial RTSphere::shadePoint(const Matrix &point) {

  if (_shader) {

    Matrix R = point - _origin;
  
    float x = R.get(0);
    float y = R.get(1);
    float z = R.get(2);
    float r = _radius;

    float phi = asin(y/r);
    float theta = acos(x / (r*cos(phi)));
    float theta2 = asin(z / (r*cos(phi)));

    float u = theta / (2*M_PI);
    float v = 1 - ((phi / M_PI) + 0.5);
    
    return _shader->shade(u, v, RTMaterial());
  }

  return getMaterial(0);
}
