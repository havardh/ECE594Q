#include "WhittedIlluminator.h"

#define C1 0.25f
#define C2 0.1f
#define C3 0.001f

RTColor WhittedIlluminator::illuminate(Intersection intersection) {
  setShape(intersection.getShape());
  setMaterial(shape->getMaterial(0));
  setPoint(intersection.getPoint());
  setLightSources(_stracer->getLightSources(&point));
  setRayOrigin(intersection.getRay().getOrigin());

  return ambient() + direct() + reflection() + refraction();
}

RTColor WhittedIlluminator::ambient() {
  return material.getDiffColor() * 0.2f;
}

RTColor WhittedIlluminator::direct() {
  return diffuse() + specular();
}

RTColor WhittedIlluminator::diffuse() {

  float f = 0;
    
  std::vector<const Light*>::iterator it;
  for (it = lightSources.begin();
       it != lightSources.end();
       ++it) {

    Matrix normal = *shape->normal(point, rayOrigin);
    normal.normalize();
    Matrix distance = (point - (*it)->getPosition());
    float d = distance.length();
    distance.normalize();
    
    float v = -normal.dot(distance);
    if (v > 0) {
      float falloff = fmin( 1.0, 1.0 / C1 + C2*d +C3*d*d );
      f += v * falloff;
    }
  }

  RTColor color = material.getDiffColor();

  f = f > 1.0 ? 1.0 : f;
  return color * f * (1 - material.getKTransparency());

}

RTColor WhittedIlluminator::specular() {
  return RTColor(0.0f, 0.0f, 0.0f);
}

RTColor WhittedIlluminator::reflection() {
  return RTColor(0.0f, 0.0f, 0.0f);
}

RTColor WhittedIlluminator::refraction() {
  return RTColor(0.0f, 0.0f, 0.0f);
}
