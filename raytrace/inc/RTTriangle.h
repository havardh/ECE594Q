#ifndef _RTTRIANGLE_H_
#define _RTTRIANGLE_H_

#include "Matrix.h"
#include "RTShape.h"

class RTTriangle : public RTShape {

public:
  RTTriangle(const Matrix &, const Matrix &, const Matrix &);
  virtual MatrixPtr intersect(const Ray );
  virtual MatrixPtr normal(const Matrix &, const Matrix &);

  const Matrix getP0() const { return _p0; }
  const Matrix getP1() const { return _p1; }
  const Matrix getP2() const { return _p2; }

private:
  Matrix _p0, _p1, _p2;

  Matrix computeN();
  Matrix computeP(Matrix&, Matrix, Matrix);

};

#endif /* _RTTRIANGLE_H_ */
