#ifndef _RTSPHERE_H_
#define _RTSPHERE_H_

#include "RTShape.h"
#include "Matrix.h"

class RTSphere : public RTShape {

 public:
  RTSphere(Matrix, float);
  virtual bool intersect(const Ray &);

 private:
  Matrix _origin;
  float _radius;

};
#endif /* _RTSPHERE_H_ */
