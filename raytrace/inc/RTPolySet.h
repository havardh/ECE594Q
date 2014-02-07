#ifndef _RTPOLYSET_H_
#define _RTPOLYSET_H_

#include <vector>
#include "Ray.h"
#include "RTShape.h"
#include "RTTriangle.h"
#include "Dbg.h"

class RTTriangle;
class RTPolySet : public RTShape {

public:
  RTPolySet() {}
  virtual IntersectionPtr intersect(const Ray );
  virtual MatrixPtr normal(const Matrix &, const Matrix &);

  void addTriangle(RTTriangle &);
  const RTTriangle getTriangle(int) const;

  virtual void print() const { DPRINTF("RTPolySet\n"); }

private:
  std::vector<RTTriangle> triangles;
  

};

#endif /* _RTPOLYSET_H_ */
