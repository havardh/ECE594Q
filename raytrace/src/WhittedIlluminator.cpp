#include "WhittedIlluminator.h"

#define C1 0.25f
#define C2 0.1f
#define C3 0.001f

float diffuseLightSourceContribution(float, float);

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

  float totalContribution = 0;
    
  std::vector<const Light*>::iterator it;
  for (it = lightSources.begin();
       it != lightSources.end();
       ++it) {

    const Light* light = *it;

    Matrix normal = shape->normal(point, rayOrigin)->normalize();
    Matrix distance = (point - light->getPosition());

    totalContribution += diffuseLightSourceContribution(
      -normal.dot(distance.normalize()),
      distance.length()
    );
  }

  RTColor baseColor = material.getDiffColor();
  totalContribution = fmin(1.0, totalContribution);
  float transpanrancyFactor = 1.0 - material.getKTransparency();

  return baseColor * totalContribution * transpanrancyFactor;

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

float diffuseLightSourceContribution(float value, float distance) {
  
  float d = distance;
  float dd = d*d;

  if (value > 0) {
      float falloff = fmin( 1.0, 1.0 / C1 + C2*d +C3*dd );
      return value * falloff;
    }
}
