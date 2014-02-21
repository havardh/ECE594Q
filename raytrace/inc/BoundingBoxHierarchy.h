#ifndef _BOUNDINGBOXHIERARCHY_H_
#define _BOUNDINGBOXHIERARCHY_H_

#include <algorithm>
#include <vector>
#include "RTShape.h"
#include "RTPolySet.h"
#include "Ray.h"
#include "BBox.h"

using std::vector;

class BoundingBoxHierarchy {

 public:
  ~BoundingBoxHierarchy();
  void build(vector<RTShape*>);
  IntersectionPtr intersect(const Ray ray);

  void print() {
    
    box.print();
    
    if (shape) shape->print();
    if (left) left->print();
    if (right) right->print();
  }

  BoundingBoxHierarchy *getLeft() { return left; }
  BoundingBoxHierarchy *getRight() {return right; }
  RTShape* getShape() { return shape; }

 private:
  BoundingBox box;
  RTShape *shape = 0;

  BoundingBoxHierarchy *left = 0;
  BoundingBoxHierarchy *right = 0;
  void sort(vector<RTShape*>::iterator first, vector<RTShape*>::iterator last, int axis);
  vector<RTShape*> flatten(vector<RTShape*>);

  BoundingBox _build(vector<RTShape*>::iterator, vector<RTShape*>::iterator, int);
};

#endif /* _BOUNDINGBOXHIERARCHY_H_ */
