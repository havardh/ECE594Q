#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_



#include "Ray.h"
#include "Matrix.h"

class Intersection;
typedef std::shared_ptr<Intersection> IntersectionPtr;

#include "RTShape.h"

class RTShape;
class Intersection {
  
public:
  Intersection() : _shape(0) {
    _ray = Ray(Matrix(0,0,0), Matrix(0,0,0));
    _point = Matrix(0,0,0);
  }
  Intersection(RTShape *shape, Ray ray, Matrix point) :
    _shape(shape), _ray(ray), _point(point) {}

  RTShape* getShape() { return _shape; }
  Ray getRay() const { return _ray; }
  Matrix getPoint() const { return _point; }

  bool operator<(const Intersection &rhs) const;

private:
  RTShape *_shape;
  Ray _ray;
  Matrix _point;

};

#endif /* _INTERSECTION_H_ */
