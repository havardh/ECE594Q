#include "PathFactory.h"
#include "Dbg.h"

Ray PathFactory::createPath(Intersection intersection) {
   
  Vector point = intersection.getPoint();
  RTShape *shape = intersection.getShape();

  Vector L = intersection.getRay().getOrigin() - point;
  Vector N = shape->normal(point)->normalize();
  Vector R = 2 * N.dot(L) * N - L;
  R.normalize();

  float brdf = 0.2;
  float rx = ((rand() / (float)RAND_MAX) * M_PI - (M_PI/2.0)) * brdf;
  float ry = ((rand() / (float)RAND_MAX) * M_PI - (M_PI/2.0)) * brdf;
  
  R.rotate(X, rx);
  R.rotate(Y, ry);

  return Ray(point + 0.00001*N, R);

}
