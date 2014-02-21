#include "BoundingBoxHierarchy.h"
#include "Dbg.h"

BoundingBoxHierarchy::~BoundingBoxHierarchy() {
  if (left) delete left;
  if (right) delete right;
}

void BoundingBoxHierarchy::build(vector<RTShape*> shapes) {

  vector<RTShape*> flattened = flatten(shapes);

  _build(flattened.begin(), flattened.end(), 0);

}

BoundingBox BoundingBoxHierarchy::_build(
  vector<RTShape*>::iterator first, 
  vector<RTShape*>::iterator last, 
  int axis) {

  if (first+1 < last) {
    sort(first, last, axis);

    vector<RTShape*>::iterator middle = first + ((last - first) / 2);

    left = new BoundingBoxHierarchy();
    right = new BoundingBoxHierarchy();

    BoundingBox leftBox = left->_build(first, middle, (axis+1)%3);
    BoundingBox rightBox = right->_build(middle, last, (axis+1)%3);

    return box = leftBox.unionWith(rightBox);
  } else if (first != last) {
    shape = *first;
    return box = shape->getBoundingBox();
  } else {
    return BoundingBox(Vector(0,0,0), Vector(0,0,0));
  }
}

IntersectionPtr BoundingBoxHierarchy::intersect(const Ray ray) {
  float u,v;
 
  if (box.intersects(ray,u,v)) {

    if (shape) {
      return shape->intersect(ray);
    } else {

      IntersectionPtr leftIntersection = left->intersect(ray);
      IntersectionPtr rightIntersection = right->intersect(ray);

      if (leftIntersection != nullptr && rightIntersection == nullptr) 
        return leftIntersection;

      if (rightIntersection != nullptr && leftIntersection == nullptr) 
        return rightIntersection;

      if (leftIntersection == nullptr && rightIntersection == nullptr) 
        return IntersectionPtr(NULL);

      if ( *leftIntersection < *rightIntersection) {
        return leftIntersection;
      } else {
            return rightIntersection;
      }
    }
  } else {
    return IntersectionPtr(NULL);
  }

}

bool xCompare(RTShape *lhs, RTShape *rhs) {
  return lhs->getPosition().x() < rhs->getPosition().x();
}

bool yCompare(RTShape *lhs, RTShape *rhs) {
  return lhs->getPosition().y() < rhs->getPosition().y();
}

bool zCompare(RTShape *lhs, RTShape *rhs) {
  return lhs->getPosition().z() < rhs->getPosition().z();
}

void BoundingBoxHierarchy::sort(
  vector<RTShape*>::iterator first, 
  vector<RTShape*>::iterator last, 
  int axis) {

  switch (axis) {
  case 0: std::sort(first, last, xCompare); break;
  case 1: std::sort(first, last, xCompare); break;
  case 2: std::sort(first, last, xCompare); break;
  }
 
}


vector<RTShape*> BoundingBoxHierarchy::flatten(vector<RTShape*> shapes) {

  vector<RTShape*> result;

  vector<RTShape*>::iterator it;
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    if ((*it)->getID() == RTPolySet::shapeID) {
      
      RTPolySet *set = (RTPolySet*)*it;
      for (int i=0; i<set->size(); i++) {

        result.push_back(set->getTrianglePointer(i));
      }
    } else {
      result.push_back(*it);
    }
    
  }

  return result;
}

