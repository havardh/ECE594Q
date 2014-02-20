#include "RTSphere.h"

#define EPSILON 0.000001

RTSphere::RTSphere(Vector origin, float radius) {
  _origin = origin;
  _radius = radius;
}

IntersectionPtr RTSphere::getIntersection(const Ray &ray) {

  Vector O = ray.getOrigin();
  Vector L = ray.getDirection();
  Vector C = this->_origin;
  float  r = this->_radius;

  Vector O_C = O-C;
  
  float a = -(L.dot(O_C));
  float b = (L.dot(O_C) * L.dot(O_C)) - (O_C).dot(O_C) + (r*r);

  if (b < 0) {
    return IntersectionPtr(NULL);
  } else {
    float d = a - (float)sqrt(b);

    Vector p(O + d * L);

    if (fabs ((ray.getOrigin() - p).length()) > 0.001) {
      return IntersectionPtr(new Intersection(this, ray, p));
    } else {
      return IntersectionPtr(NULL);
    }
  }
}

// http://mathworld.wolfram.com/Point-LineDistance3-Dimensional.html
IntersectionPtr RTSphere::intersect(const Ray ray) {

  Vector x0 = _origin;
  Vector x1 = ray.getOrigin();
  Vector x2 = ray.getOrigin() + ray.getDirection();


  if ((x1 - x0).length() < (x2 - x0).length()) {
    return IntersectionPtr(NULL);
  }

  float d = ((x2 - x1).cross(x1 - x0)).length() / ((x2-x1).length());

  if (_radius >= d) {
    return getIntersection(ray);
  } else {
    return IntersectionPtr(NULL);
  }
  
}

VectorPtr RTSphere::normal(const Vector &point) {


  Vector direction = point - _origin;
  return VectorPtr(new Vector(direction.normalize()));

}

void RTSphere::interpolateUV(float &u, float &v, const Vector point) {

  Vector R = _origin - point;
  R.normalize();

  u = (float) (0.5 + atan2(R.z(), R.x()) / (2 * M_PI));
  v = (float) (0.5 - asin(R.y()) / M_PI);
  
}

const RTMaterial RTSphere::interpolateMaterial(const Vector &point) {
  (void) point;
  return getMaterial(0);
}

BoundingBox RTSphere::getBoundingBox() const {
  float x = getOrigin().x() - _radius;
  float y = getOrigin().y() - _radius;
  float z = getOrigin().z() - _radius;

  Vector origin(x,y,z);
  float diameter = _radius*2;
  Vector delta(diameter, diameter, diameter);

  return BoundingBox(origin, delta);
}
