#ifndef _RTPOLYSET_H_
#define _RTPOLYSET_H_

#include <vector>
#include "Ray.h"
#include "RTShape.h"
#include "RTTriangle.h"

class RTPolySet : public RTShape {

public:
  RTPolySet() {}

  void addTriangle(RTTriangle &);
  const RTTriangle getTriangle(int) const;
  virtual MatrixPtr intersect(const Ray &);

private:
  std::vector<RTTriangle> triangles;
  

};

#endif /* _RTPOLYSET_H_ */
