#ifndef _SURFACEAREAHEURISTIC_H_
#define _SURFACEAREAHEURISTIC_H_

#include "SplitHeuristic.h"
#include "RTSphere.h"
#include <algorithm>
#include <limits>

#define COSTTRAVERSE 1
#define COSTINTERSECT 10

class SurfaceAreaHeuristic : public SplitHeuristic {
 public:
  virtual float findMedian(BoundingBox box, vector<RTShape*>, int) ;

 private:
  int _axis;
  vector<RTShape*> *_shapes;
  BoundingBox _box;

  float calculateCost(float,int);
  float calculateLeftArea(float);
  float calculateRightArea(float);
  void sort();
};

#endif /* _SURFACEAREAHEURISTIC_H_ */
