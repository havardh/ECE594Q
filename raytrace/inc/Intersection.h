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
  Intersection(RTShape *shape, Ray ray, Matrix point) :
    _shape(shape), _ray(ray), _point(point) {}

  RTShape* getShape() { return _shape; }
  Ray getRay() { return _ray; }
  Matrix getPoint() { return _point; }

private:
  RTShape *_shape;
  Ray _ray;
  Matrix _point;

};

#endif /* _INTERSECTION_H_ */
