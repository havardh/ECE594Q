#ifndef _SPLITHEURISTIC_H_
#define _SPLITHEURISTIC_H_

#include "RTShape.h"
#include "BoundingBox.h"
#include <vector>

using std::vector;

class SplitHeuristic {
 public:
  virtual float findMedian(BoundingBox, vector<RTShape*>, int) = 0;
  
};

#endif /* _SPLITHEURISTIC_H_ */
