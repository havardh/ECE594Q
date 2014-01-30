#include "MatrixTestHelper.h"

static void renderNonMatchingMatrices(float *expected, Matrix actual, int ei, int ej) {

  (void) expected;
  (void) ei;
  (void) ej;
  
  int m = actual.getM();
  int n = actual.getN();

  char err[1024];
  sprintf(err, "%s", "Actual: \n  ");

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      sprintf(err, "%s %4.4f ", err, actual.get(i,j));
    }
    sprintf(err, "%s %s", err, "\n  ");
   }
  sprintf(err, "%s%s", err, "Expected:\n  ");

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {


      sprintf(err, "%s %4.4f ", err, expected[ n*i+j]);
    }
    sprintf(err, "%s %s", err, "\n  ");
  }
  
  FAIL(err);

}

void MATRIX_EQUALS(float *expected, Matrix actual, double tolerance) {

  int m = actual.getM();
  int n = actual.getN();

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      if (fabs(expected[i*n+j] - actual.get(i,j)) >= tolerance) {
        renderNonMatchingMatrices(expected, actual, i,j);
        break;
      }
    }
  }

}

