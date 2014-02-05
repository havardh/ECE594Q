#ifndef _RTSPHERE_H_
#define _RTSPHERE_H_

#include "RTShape.h"
#include "Matrix.h"

class RTSphere : public RTShape {

 public:
  RTSphere(Matrix, float);
  virtual MatrixPtr intersect(const Ray &);

  const Matrix getOrigin() const { return _origin; }
  float getRadius() const { return _radius; }

 private:
  Matrix _origin;
  float _radius;

};
#endif /* _RTSPHERE_H_ */
