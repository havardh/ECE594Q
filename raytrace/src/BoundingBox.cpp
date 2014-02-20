#include "BBox.h"
#include "Dbg.h"

#define X 0
#define Y 1
#define Z 2

BoundingBox::BoundingBox() : _origin(0,0,0), _delta(0,0,0) {}

BoundingBox::BoundingBox(Vector origin, Vector delta) :
  _origin(origin), _delta(delta) {}

BoundingBoxes BoundingBox::split(float m, int axis) const {

  //DPRINTF("Original\n");
  //this->print();
  
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

  //DPRINTF("First\n");
  //first.print();
  //DPRINTF("Second\n");
  //second.print();

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

/*bool BoundingBox::intersects(Ray ray, float &tmin, float &tmax) const {
  
  float dirfracx = 1.0f / ray.getDirection().get(0);
  float dirfracy = 1.0f / ray.getDirection().get(1);
  float dirfracz = 1.0f / ray.getDirection().get(2);

  Vector lb = getOrigin();
  Vector rt = getOrigin() + getDelta();

  Vector o = ray.getOrigin();
  float s1 = (lb.get(0) - o.get(0)) * dirfracx;
  float s2 = (rt.get(0) - o.get(0)) * dirfracx;
  float s3 = (lb.get(1) - o.get(1)) * dirfracx;
  float s4 = (rt.get(1) - o.get(1)) * dirfracx;
  float s5 = (lb.get(2) - o.get(2)) * dirfracx;
  float s6 = (rt.get(2) - o.get(2)) * dirfracx;

  tmin = fmax(fmax(fmin(s1, s2), fmin(s3, s4)), fmin(s5, s6));
  tmax = fmin(fmin(fmax(s1, s2), fmax(s3, s4)), fmax(s5, s6));

  if (tmax < 0) {
    return false;
  }

  if (tmin > tmax) {
    return false;
  }

  return true;
  }*/

bool BoundingBox::intersects(Ray ray, float &tmin, float &tmax) const {

  Vector min = getOrigin();
  Vector max = getOrigin() + getDelta();

  tmin = (min.x() - ray.getOrigin().x()) / ray.getDirection().x();
  tmax = (max.x() - ray.getOrigin().x()) / ray.getDirection().x();

  if (tmin > tmax) std::swap(tmin, tmax);

  float tymin = (min.y() - ray.getOrigin().y()) / ray.getDirection().y();
  float tymax = (max.y() - ray.getOrigin().y()) / ray.getDirection().y();

  if (tymin > tymax) std::swap(tymin, tymax);

  if (tymin < tmin) tmin = tymin;
  if (tymax < tmax) tmax = tymax;

  float tzmin = (min.z() - ray.getOrigin().z()) / ray.getDirection().z();
  float tzmax = (max.z() - ray.getOrigin().z()) / ray.getDirection().z();

  if (tzmin > tzmax) std::swap(tzmin, tzmax);

  if (tzmin < tmin) tmin = tzmin;
  if (tzmax < tmax) tmax = tzmax;

  if (tmax < 0) return false;
  if (tmin < 0) tmin = 0;

  return isfinite(tmin) && isfinite(tmax);
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
