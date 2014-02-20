#ifndef _MEANHEURISTIC_H_
#define _MEANHEURISTIC_H_

#include "SplitHeuristic.h"

class MeanHeuristic : public SplitHeuristic {
 public:
  virtual float findMedian(BoundingBox box, vector<RTShape*>, int) ;

};

#endif /* _MEANHEURISTIC_H_ */
