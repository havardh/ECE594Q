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
};

#endif /* _MATRIXFACTORY_H_ */
