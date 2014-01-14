#ifndef _MATRIXFACTORY_H_
#define _MATRIXFACTORY_H_

#include "Matrix.h"

class MatrixFactory {

 public:
  static Matrix createIdentity(int);

  static Matrix createTranslation(const Matrix &);
  static Matrix createScale(const Matrix &);
};

#endif /* _MATRIXFACTORY_H_ */
