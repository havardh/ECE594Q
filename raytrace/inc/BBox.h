#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "Vector.h"
#include "Ray.h"
#include <utility>

using std::pair;

class BoundingBox {

public:
  BoundingBox();
  BoundingBox(Vector, Vector);
  
  void setOrigin(Vector);
  void setDelta(Vector);
  Vector getOrigin() const;
  Vector getDelta() const;

  pair<BoundingBox,BoundingBox> split(float,int) const;

  bool intersects(const BoundingBox &box) const;
  bool intersects(Ray, float&, float&) const;
  BoundingBox unionWith(const BoundingBox &box) const;
  Vector center() const;

  void print() const {
    _origin.print();
    (_origin+_delta).print();
  }

private:
  Vector _origin;
  Vector _delta;


  bool intersectsOnAxis(const BoundingBox &box, int axis) const;
};

typedef pair<BoundingBox,BoundingBox> BoundingBoxes;

#endif /* _BOUNDINGBOX_H_ */
