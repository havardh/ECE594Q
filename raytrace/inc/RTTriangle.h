#ifndef _RTTRIANGLE_H_
#define _RTTRIANGLE_H_

#include <cmath>
#include "Matrix.h"
#include "RTShape.h"
#include "RTPolySet.h"
#include "Dbg.h"

class RTPolySet;
class RTTriangle : public RTShape {

public:
  RTTriangle(const Matrix &, const Matrix &, const Matrix &);
  virtual IntersectionPtr intersect(const Ray );
  virtual MatrixPtr normal(const Matrix &, const Matrix &);

  virtual int getMaterialCount() const;
  virtual const RTMaterial getMaterial(int) const;

  virtual RTMaterial shadePoint(const Matrix&);

  const Matrix getP0() const { return _p0; }
  const Matrix getP1() const { return _p1; }
  const Matrix getP2() const { return _p2; }
  virtual void print() const { 
    DPRINTF("Triangle\n"); 
    _p0.printPoint(); 
    _p1.printPoint();  
    _p2.printPoint();  
  }

  void setParent(RTPolySet *parent) {
    _parent = parent;
  }

private:
  RTPolySet *_parent;

  Matrix _p0, _p1, _p2;

  Matrix computeN();
  Matrix computeP(Matrix&, Matrix, Matrix);

};

#endif /* _RTTRIANGLE_H_ */
