#ifndef _RTSHAPE_H_
#define _RTSHAPE_H_

#include "Ray.h"

class RTShape {
  
 public:
  virtual ~RTShape() {}
  virtual bool intersect(const Ray &) = 0;

    
};

#endif /* _RTSHAPE_H_ */
