#include "PathFactory.h"
#include "Dbg.h"

Ray PathFactory::createPath(Intersection intersection) {
   
  Vector point = intersection.getPoint();
  RTShape *shape = intersection.getShape();

  // Calculate outgoing ray
  Vector L = intersection.getRay().getOrigin() - point;
  Vector N = shape->normal(point)->normalize();
  Vector R = 2 * N.dot(L) * N - L;
  R.normalize();

  // Calculate BRDF
  RTMaterial m = shape->interpolateMaterial(point);
  RTColor s = m.getSpecColor();
  float r = s.getRed(), g = s.getGreen(), b = s.getBlue();
  float brdf = 1-fmin(1, sqrt(r*r + g*g + b*b)) * 0.5;

  // Add diffuse randomness
  float rx = ((rand() / (float)RAND_MAX) * M_PI - (M_PI/2.0)) * brdf;
  float ry = ((rand() / (float)RAND_MAX) * M_PI - (M_PI/2.0)) * brdf;
  R.rotate(X, rx);
  R.rotate(Y, ry);

  return Ray(point + 0.00001*N, R);

}
