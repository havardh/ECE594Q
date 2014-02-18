#include "Snell.h"

Vector Snell::direction(float n1, float n2, Vector N, Vector I) {

  float theta1 = acos( N.dot(I) / (N.length() * I.length()) );
  float theta2 = asin( (sin(theta1) * n1) / n2 );

  if (fabs(theta1) < 0.000001 && fabs(theta2) < 0.000001) {
    Vector D = -I;
    return D.normalize();
  }

  if (fabs(theta1) - M_PI/2.0 < 0.000001) {
    return I.normalize();
  }

  Vector Q = cos(theta1) * N;
  Vector M = (sin(theta2) / sin(theta1)) * (Q - I);
  Vector P = -cos(theta2) * N;

  Vector T = M + P;

  return T;
}

/*
// http://steve.hollasch.net/cgindex/render/refraction.txt
Vector Snell::direction(float n1, float n2, Vector N, Vector I) {

  float eta, c1, cs2;

  eta = n1 / n2;
  c1 = -I.dot(N);
  cs2 = 1 - eta * eta * (1 - c1 * c1);

  if (cs2 < 0) printf("tir\n"); // total internal reflectation
  
  Vector T = eta * I + (eta * c1 - sqrt(cs2)) * N;

  return T;
}
*/
