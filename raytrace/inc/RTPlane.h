#ifndef _RTPLANE_H_
#define _RTPLANE_H_

#include "RTPolySet.h"

class RTPlane : public RTPolySet {
 public:
  bool isToLeftOf(Ray,int);

};

#endif /* _RTPLANE_H_ */
