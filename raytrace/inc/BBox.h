#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "Matrix.h"
#include <utility>

using std::pair;

class BoundingBox {

public:
  BoundingBox();
  BoundingBox(Matrix, Matrix);
  
  void setOrigin(Matrix);
  void setDelta(Matrix);
  Matrix getOrigin() const;
  Matrix getDelta() const;

  pair<BoundingBox,BoundingBox> split(float,int) const;

  bool intersects(const BoundingBox &box) const;
  BoundingBox unionWith(const BoundingBox &box) const;
  Matrix center() const;

  void print() const {
    _origin.printPoint();
    _delta.printPoint();
  }

private:
  Matrix _origin;
  Matrix _delta;


  bool intersectsOnAxis(const BoundingBox &box, int axis) const;
};

typedef pair<BoundingBox,BoundingBox> BoundingBoxes;

#endif /* _BOUNDINGBOX_H_ */
