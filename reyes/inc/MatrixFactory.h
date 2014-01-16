#ifndef _MATRIXFACTORY_H_
#define _MATRIXFACTORY_H_

#include "Matrix.h"
#include "Axis.h"
#include <cmath>

class Matrix;

class MatrixFactory {

 public:

  static Matrix createIdentity(int);

  static Matrix createTranslation(const Matrix &);
  static Matrix createScale(const Matrix &);
  static Matrix createRotation(Axis, float);
  static Matrix createPerspectiveProjection(float theta, float r, float hither, float yon);
  static Matrix createOrthogonalProjection(float left, float right, float top, float bottom, float near, float far);
};

#endif /* _MATRIXFACTORY_H_ */
