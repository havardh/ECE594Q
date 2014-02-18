#ifndef _RTSPHERE_H_
#define _RTSPHERE_H_

#include <cmath>
#include "RTShape.h"
#include "Vector.h"
#include "Dbg.h"

class RTSphere : public RTShape {

public:
  RTSphere(Vector, float);
  virtual IntersectionPtr intersect(const Ray);
  virtual VectorPtr normal(const Vector &);

  const Vector getOrigin() const { return _origin; }
  float getRadius() const { return _radius; }
  virtual void print() const { DPRINTF("RTSphere\n"); }
  virtual Vector getPosition() const { return _origin; }
  virtual BoundingBox getBoundingBox() const;

  virtual void interpolateUV(float &, float &, const Vector);
  virtual const RTMaterial interpolateMaterial(const Vector&);

  virtual int getID() { return RTSphere::shapeID; }
  const static int shapeID = 1;

private:
  Vector _origin;
  float _radius;



  IntersectionPtr getIntersection(const Ray &);

};
#endif /* _RTSPHERE_H_ */
