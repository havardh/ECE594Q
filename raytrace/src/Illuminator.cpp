#include "Illuminator.h"

void Illuminator::setLocalVariables(Intersection intersection) {
  setShape(intersection.getShape());
  setMaterial(shape->getMaterial(0));
  setPoint(intersection.getPoint());
  setRayDirection(intersection.getRay().getDirection());
  setRayOrigin(intersection.getRay().getOrigin());
  setIntersection(intersection);
}

RTColor Illuminator::diffuse(const Light *light) {

  Vector N = -shape->normal(point)->normalize();
  Vector Dj = light->getDirectionFrom(point);
  
  float value = fmax(0, (-N).dot(Dj.normalize()));
  RTColor Cd = material.getDiffColor();
  float kt = material.getKTransparency();

  return Cd * (1.0f - kt)  * value;

}

RTColor Illuminator::specular(const Light *light) {

  Vector V = (rayOrigin - point);
  Vector L = light->getDirectionFrom(point);
  V.normalize();
  L.normalize();

  RTColor ks = material.getSpecColor();
  float q = material.getShininess() * 128;

  Vector N = shape->normal(point)->normalize();

  Vector R = 2 * N.dot(L) * N - L;
  R.normalize();

  float x = R.dot(V);

  RTColor value = ks * pow(x > 0 ? x : 0, q);

  return value;
}

float Illuminator::computeFattj(const Light *light) {
  
  if (light->getType() == POINT) {

    float distance = (light->getPosition() - point).length();

    float d = distance;
    float dd = d*d;

    return fmin( 1.0, 1.0 / (C1 + C2*d +C3*dd) );
  } else {
    return 1;
  }
}
