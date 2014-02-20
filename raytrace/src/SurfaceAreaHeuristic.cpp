#include "SurfaceAreaHeuristic.h"

bool xCompare(const RTShape *lhs, const RTShape *rhs);
bool yCompare(const RTShape *lhs, const RTShape *rhs);
bool zCompare(const RTShape *lhs, const RTShape *rhs);

float SurfaceAreaHeuristic::findMedian(BoundingBox box, vector<RTShape*> shapes, int axis) {
  
  _box = box;
  _axis = axis;
  _shapes = &shapes;

  sort();

  float cost;
  float bestpos = 0;
  float bestcost = calculateCost(shapes[0]->getBoundingBox().getOrigin().get(axis),0);

  float bmin = box.getOrigin().get(axis);
  float bmax = box.getOrigin().get(axis) + box.getDelta().get(axis);
  
  vector<RTShape*>::iterator it;
  int i=0; 
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    BoundingBox sBox = (*it)->getBoundingBox();

    float min = sBox.getOrigin().get(axis);
    float max = sBox.getOrigin().get(axis) + sBox.getDelta().get(axis);

    if ((cost = calculateCost(min,i)) < bestcost && min > bmin && fabs(min - bmin) > 0.0001) {
      //DPRINTF("%f %f %f\n", min, bmin, min-bmin);
      bestcost = cost; bestpos = min;
    }
    

    //DPRINTF("%d\n", cost);

    if ((cost = calculateCost(max,i)) < bestcost && max < bmax && fabs(max - bmax) > 0.0001) {
      bestcost = cost; bestpos = max;
    }
    //DPRINTF("%d\n", cost);

    i += 1;
  }

  //DPRINTF("\n"); box.print();

  //DPRINTF("%d %d %f\n", i, axis, bestpos);
  return bestpos;
}

void SurfaceAreaHeuristic::sort() {
  switch (_axis) {
  case 0: std::sort(_shapes->begin(), _shapes->end(), xCompare); break;
  case 1: std::sort(_shapes->begin(), _shapes->end(), yCompare); break;
  case 2: std::sort(_shapes->begin(), _shapes->end(), zCompare); break;
  }
}

float SurfaceAreaHeuristic::calculateCost(float pos, int i) {

  float leftArea = calculateLeftArea(pos);
  float rightArea = calculateRightArea(pos);
  int leftCount = i;
  int rightCount = _shapes->size() - 1;

  float cost = COSTTRAVERSE + COSTINTERSECT * ( leftArea*leftCount + rightArea*rightCount );

  //DPRINTF("%f\n", cost);

  return cost;

}

float SurfaceAreaHeuristic::calculateLeftArea(float pos) {

  int k1 = (_axis + 1) % 3;
  int k2 = (_axis + 2) % 3;

  float h = pos - _box.getOrigin().get(_axis);
  float w = _box.getDelta().get(k1);
  float l = _box.getDelta().get(k2);

  //DPRINTF("%f\n", h*w);

  return 2*(h*w + h*l + l*w);
}

float SurfaceAreaHeuristic::calculateRightArea(float pos) {

  int k1 = (_axis + 1) % 3;
  int k2 = (_axis + 2) % 3;

  float h = _box.getDelta().get(_axis) - (pos - _box.getOrigin().get(_axis));
  float w = _box.getDelta().get(k1);
  float l = _box.getDelta().get(k2);

  //DPRINTF("%f\n", h*w);

  return 2*(h*w + h*l + l*w);
}

bool xCompare(const RTShape *lhs, const RTShape *rhs) {
  BoundingBox lBox = lhs->getBoundingBox();
  BoundingBox rBox = rhs->getBoundingBox();

  if (lBox.getOrigin().x() < rBox.getOrigin().x()) {
    return true;
  }

  if ((lBox.getOrigin().x() + lBox.getDelta().x())
      < (rBox.getOrigin().x() + rBox.getDelta().x()) ) {
    return true;
  }

  return false;

}

bool yCompare(const RTShape *lhs, const RTShape *rhs) {
  BoundingBox lBox = lhs->getBoundingBox();
  BoundingBox rBox = rhs->getBoundingBox();

  if (lBox.getOrigin().y() < rBox.getOrigin().y()) {
    return true;
  }

  if ((lBox.getOrigin().y() + lBox.getDelta().y())
      < (rBox.getOrigin().y() + rBox.getDelta().y()) ) {
    return true;
  }

  return false;

}

bool zCompare(const RTShape *lhs, const RTShape *rhs) {
  BoundingBox lBox = lhs->getBoundingBox();
  BoundingBox rBox = rhs->getBoundingBox();

  if (lBox.getOrigin().z() < rBox.getOrigin().z()) {
    return true;
  }

  if ((lBox.getOrigin().z() + lBox.getDelta().z())
      < (rBox.getOrigin().z() + rBox.getDelta().z()) ) {
    return true;
  }

  return false;

}
