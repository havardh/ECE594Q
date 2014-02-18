#include "BBox.h"

#define X 0
#define Y 1
#define Z 2

BoundingBox::BoundingBox() : _origin(0,0,0), _delta(0,0,0) {}

BoundingBox::BoundingBox(Vector origin, Vector delta) :
  _origin(origin), _delta(delta) {}

BoundingBoxes BoundingBox::split(float m, int axis) const {
  
  Vector origin = getOrigin();
  Vector delta = getDelta();
  
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

  Vector origin(
    fmin(getOrigin().x(), box.getOrigin().x()),
    fmin(getOrigin().y(), box.getOrigin().y()),
    fmin(getOrigin().z(), box.getOrigin().z())
  );
  
  float max_x = fmax(
    getOrigin().x()+getDelta().x(),
    box.getOrigin().x()+box.getDelta().x()
  );
  
  float max_y = fmax(
    getOrigin().y()+getDelta().y(),
    box.getOrigin().y()+box.getDelta().y()
  );
  
  float max_z = fmax(
    getOrigin().z()+getDelta().z(),
    box.getOrigin().z()+box.getDelta().z()
  );

  Vector delta(
    max_x - origin.x(),
    max_y - origin.y(),
    max_z - origin.z()
  );

  return BoundingBox(origin, delta);

}

Vector BoundingBox::center() const {

  return getOrigin() + 0.5 * getDelta();

}

void BoundingBox::setOrigin(Vector origin) {
  _origin = origin;
}

void BoundingBox::setDelta(Vector delta) {
  _delta = delta;
}

Vector BoundingBox::getOrigin() const {
  return _origin;
}

Vector BoundingBox::getDelta() const {
  return _delta;
}
