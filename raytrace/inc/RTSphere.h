#ifndef _RTSPHERE_H_
#define _RTSPHERE_H_

#include <cmath>
#include "RTShape.h"
#include "Matrix.h"
#include "Dbg.h"

class RTSphere : public RTShape {

 public:
  RTSphere(Matrix, float);
  virtual IntersectionPtr intersect(const Ray);
  virtual MatrixPtr normal(const Matrix &);

  const Matrix getOrigin() const { return _origin; }
  float getRadius() const { return _radius; }
  virtual void print() const { DPRINTF("RTSphere\n"); }

  virtual RTMaterial shadePoint(const Matrix&);
  virtual bool shadeIntersection(const Intersection&);

 private:
  Matrix _origin;
  float _radius;

  IntersectionPtr getIntersection(const Ray &);
  void interpolateUV(float &, float &, const Matrix &);

};
#endif /* _RTSPHERE_H_ */
