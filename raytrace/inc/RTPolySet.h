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
  RTPolySet() : midpoint(0,0,0) {}
  virtual IntersectionPtr intersect(const Ray );
  virtual MatrixPtr normal(const Matrix &);


  void addTriangle(RTTriangle &);
  const RTTriangle getTriangle(int) const;
  void calculateMidpoint();
  const Matrix getMidpoint() const { return midpoint; }

  virtual void print() const { DPRINTF("RTPolySet\n"); }

  virtual void interpolateUV(float &u, float &v, const Matrix &point);
  virtual const RTMaterial interpolateMaterial(const Matrix&);

private:
  std::vector<RTTriangle> triangles;
  Matrix midpoint;


};

#endif /* _RTPOLYSET_H_ */
