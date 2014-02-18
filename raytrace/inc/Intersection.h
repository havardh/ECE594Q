#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_



#include "Ray.h"
#include "Vector.h"

class Intersection;
typedef std::shared_ptr<Intersection> IntersectionPtr;

#include "RTShape.h"

class RTShape;
class Intersection {
  
public:
  Intersection() : _shape(0) {
    _ray = Ray(Vector(0,0,0), Vector(0,0,0));
    _point = Vector(0,0,0);
  }
  Intersection(RTShape *shape, Ray ray, Vector point) :
    _shape(shape), _ray(ray), _point(point) {}

  RTShape* getShape() { return _shape; }
  Ray getRay() const { return _ray; }
  Vector getPoint() const { return _point; }

  bool operator<(const Intersection &rhs) const;

private:
  RTShape *_shape;
  Ray _ray;
  Vector _point;

};

#endif /* _INTERSECTION_H_ */
