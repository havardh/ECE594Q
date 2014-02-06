#ifndef _RTPOLYSET_H_
#define _RTPOLYSET_H_

#include <vector>
#include "Ray.h"
#include "RTShape.h"
#include "RTTriangle.h"

class RTPolySet : public RTShape {

public:
  RTPolySet() {}
  virtual MatrixPtr intersect(const Ray );
  virtual MatrixPtr normal(const Matrix &, const Matrix &);

  void addTriangle(RTTriangle &);
  const RTTriangle getTriangle(int) const;

private:
  std::vector<RTTriangle> triangles;
  

};

#endif /* _RTPOLYSET_H_ */