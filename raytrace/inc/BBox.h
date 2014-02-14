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

  pair<BoundingBox,BoundingBox> split(float,int);

  bool intersects(const BoundingBox &box);

private:
  Matrix _origin;
  Matrix _delta;


  bool intersectsOnAxis(const BoundingBox &box, int axis);
};

typedef pair<BoundingBox,BoundingBox> BoundingBoxes;

#endif /* _BOUNDINGBOX_H_ */
