#include "MeanHeuristic.h"
#include "Dbg.h"

float MeanHeuristic::findMedian(BoundingBox box, vector<RTShape*> shapes, int axis) {
  vector<RTShape*>::iterator it;
  
  float m = 0;
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    m += (*it)->getBoundingBox().center().get(axis);
  }
  return m / shapes.size();
}
