#include "WhittedIlluminator.h"

#define C1 0.25f
#define C2 0.1f
#define C3 0.001f
#define REFLECTIONS 10

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

  RTColor totalContribution(0,0,0);

  Matrix V = (rayOrigin - point);
  V.normalize();

  RTColor ks = material.getSpecColor();
  float q = material.getShininess() * 128;

  std::vector<const Light*>::iterator it;
  for (it = lightSources.begin();
       it != lightSources.end();
       ++it) {

    const Light* light = *it;
  
    Matrix L = light->getPosition() - point;
    Matrix N = shape->normal(point, rayOrigin)->normalize();
    Matrix R = 2* N.dot(L) * N - L;
    R.normalize();

    Matrix distance = (point - light->getPosition());
    RTColor value = ks * pow(R.dot(V), q);

    RTColor scaled(
      diffuseLightSourceContribution(value.getRed(), distance.length()),
      diffuseLightSourceContribution(value.getGreen(), distance.length()),
      diffuseLightSourceContribution(value.getBlue(), distance.length())

    );

    totalContribution = (totalContribution + scaled) * light->getColor();
    
  }

  return totalContribution;
}

RTColor WhittedIlluminator::reflection() {

  if (_reflectionsComputed++ < REFLECTIONS) {

    RTColor ks = material.getSpecColor();

    Matrix L = rayOrigin - point;
    Matrix N = shape->normal(point, rayOrigin)->normalize();
    Matrix R = 2* N.dot(L) * N - L;
    R.normalize();
    
    Ray ray(point, R);

    IntersectionPtr intersection = _scene->intersect(ray);

    if (intersection != nullptr) {
      return ks*illuminate(*intersection);
    }
    
  }

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
