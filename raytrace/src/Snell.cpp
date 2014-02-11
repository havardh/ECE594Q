#include "Snell.h"

Matrix Snell::direction(float n1, float n2, Matrix N, Matrix I) {

  float theta1 = acos( N.dot(I) / (N.length() * I.length()) );
  float theta2 = asin( (sin(theta1) * n1) / n2 );

  if (fabs(theta1) < 0.000001 && fabs(theta2) < 0.000001) {
    Matrix D = -I;
    return D.normalize();
  }

  if (fabs(theta1) - M_PI/2.0 < 0.000001) {
    return I.normalize();
  }

  Matrix Q = cos(theta1) * N;
  Matrix M = (sin(theta2) / sin(theta1)) * (Q - I);
  Matrix P = -cos(theta2) * N;

  Matrix T = M + P;

  return T;
}

/*
// http://steve.hollasch.net/cgindex/render/refraction.txt
Matrix Snell::direction(float n1, float n2, Matrix N, Matrix I) {

  float eta, c1, cs2;

  eta = n1 / n2;
  c1 = -I.dot(N);
  cs2 = 1 - eta * eta * (1 - c1 * c1);

  if (cs2 < 0) printf("tir\n"); // total internal reflectation
  
  Matrix T = eta * I + (eta * c1 - sqrt(cs2)) * N;

  return T;
}
*/
