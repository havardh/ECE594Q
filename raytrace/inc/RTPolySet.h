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
  RTPolySet() : midpoint(0,0,0) {
    //triangles.reserve(500);
  }
  virtual IntersectionPtr intersect(const Ray );
  virtual VectorPtr normal(const Vector &);


  void addTriangle(RTTriangle);
  const RTTriangle getTriangle(int) const;
  RTTriangle* getTrianglePointer(int);
  int size() const { return triangles.size(); }
  void calculateMidpoint();
  const Vector getMidpoint() const { return midpoint; }
  virtual Vector getPosition() const { 
    return Vector(0,0,0);
  }
  virtual BoundingBox getBoundingBox();
  virtual void print() const { DPRINTF("RTPolySet\n"); }

  virtual void interpolateUV(float &u, float &v, const Vector point);
  virtual const RTMaterial interpolateMaterial(const Vector&);

  virtual int getID() { return RTPolySet::shapeID; }
  const static int shapeID = 2;
  
protected:
  std::vector<RTTriangle> triangles;
  Vector midpoint;

  

};

#endif /* _RTPOLYSET_H_ */
