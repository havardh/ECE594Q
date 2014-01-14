#include "MatrixTestHelper.h"

void MATRIX_EQUALS(float *expected, Matrix & actual, double tolerance) {

  int m = actual.getM();
  int n = actual.getN();

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      DOUBLES_EQUAL(expected[i*n+j], actual.get(i,j), tolerance);
    }
  }

}
