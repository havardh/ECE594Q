#ifndef _MATRIXTESTHELPER_H_
#define _MATRIXTESTHELPER_H_

#include "CppUTest/CommandLineTestRunner.h"
#include <cmath>
#include "Matrix.h"

void MATRIX_EQUALS(float *expected, Matrix actual, double tolerance);

#define VECTOR_EQUAL(x,y,z, matrix)             \
  DOUBLES_EQUAL(x, matrix.get(0), 0.0001);      \
  DOUBLES_EQUAL(y, matrix.get(1), 0.0001);      \
  DOUBLES_EQUAL(z, matrix.get(2), 0.0001); 


#endif /* _MATRIXTESTHELPER_H_ */
