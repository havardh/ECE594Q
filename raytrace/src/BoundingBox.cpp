#include "BBox.h"

#define X 0
#define Y 1
#define Z 2

BoundingBox::BoundingBox() : _origin(0,0,0), _delta(0,0,0) {}

BoundingBox::BoundingBox(Matrix origin, Matrix delta) :
  _origin(origin), _delta(delta) {}

BoundingBoxes BoundingBox::split(float m, int axis) const {
  
  Matrix origin = getOrigin();
  Matrix delta = getDelta();
  
  BoundingBox first = *this;
  delta.set(axis, m - getOrigin().get(axis));
  first.setDelta(delta);

  BoundingBox second = *this;
  delta.set(axis, (getOrigin().get(axis) + getDelta().get(axis)) - m );
  origin.set(axis,m);
  second.setOrigin(origin);
  second.setDelta(delta);

  return BoundingBoxes(first, second);
  
}

bool BoundingBox::intersectsOnAxis(const BoundingBox &box, int axis) const {
  float p1x0 = getOrigin().get(axis);
  float p1x1 = p1x0 + getDelta().get(axis);
  float p2x0 = box.getOrigin().get(axis);
  float p2x1 = p2x0 + box.getDelta().get(axis);
  
  bool point0InBox = (p1x0 <= p2x0 && p2x0 <= p1x1);
  bool point1InBox = (p1x0 <= p2x1 && p2x1 <= p1x1);
  bool contained = (p2x0 <= p1x0 && p1x1 <= p2x1);

  return point0InBox || point1InBox || contained;
}

bool BoundingBox::intersects(const BoundingBox &box) const {

  bool x = intersectsOnAxis(box, X);
  bool y = intersectsOnAxis(box, Y);
  bool z = intersectsOnAxis(box, Z);

  return x && y && z;
}

BoundingBox BoundingBox::unionWith(const BoundingBox &box) const {

  Matrix origin(
    fmin(getOrigin().get(0), box.getOrigin().get(0)),
    fmin(getOrigin().get(1), box.getOrigin().get(1)),
    fmin(getOrigin().get(2), box.getOrigin().get(2))
  );
  
  float max_x = fmax(
    getOrigin().get(0)+getDelta().get(0),
    box.getOrigin().get(0)+box.getDelta().get(0)
  );
  
  float max_y = fmax(
    getOrigin().get(1)+getDelta().get(1),
    box.getOrigin().get(1)+box.getDelta().get(1)
  );
  
  float max_z = fmax(
    getOrigin().get(2)+getDelta().get(2),
    box.getOrigin().get(2)+box.getDelta().get(2)
  );

  Matrix delta(
    max_x - origin.get(0),
    max_y - origin.get(1),
    max_z - origin.get(2)
  );

  return BoundingBox(origin, delta);

}

Matrix BoundingBox::center() const {

  return getOrigin() + 0.5 * getDelta();

}

void BoundingBox::setOrigin(Matrix origin) {
  _origin = origin;
}

void BoundingBox::setDelta(Matrix delta) {
  _delta = delta;
}

Matrix BoundingBox::getOrigin() const {
  return _origin;
}

Matrix BoundingBox::getDelta() const {
  return _delta;
}
