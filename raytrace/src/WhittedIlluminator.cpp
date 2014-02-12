#include "WhittedIlluminator.h"

// Constants used for computing light falloff
#define C1 0.25f
#define C2 0.1f
#define C3 0.001f

// How many recursive steps in reflection
#define REFLECTIONS 10

#define ETA1 1.0 // refraction index for air
#define ETA2 1.5 // refraction index for solid object


RTColor WhittedIlluminator::illuminate(Intersection intersection) {
  setShape(intersection.getShape());
  setMaterial(shape->getMaterial(0));
  setPoint(intersection.getPoint());
  setRayDirection(intersection.getRay().getDirection());
  setRayOrigin(intersection.getRay().getOrigin());
  //DPRINTF("\n");
  return ambient() + 
    direct() + 
    reflection() + 
    refraction() +
    0;
}

WhittedIlluminator* WhittedIlluminator::newIlluminator(
  ShadowTracer *shadowTracer, Scene *scene) {
  return 0;
}

RTColor WhittedIlluminator::ambient() {
  return material.getDiffColor() * 0.2f;
}

RTColor WhittedIlluminator::direct() {

  RTColor total;

  LightIter it;
  
  if (!_scene) return RTColor::BLACK;

  
  for (it = _scene->lightsBegin(); it != _scene->lightsEnd(); ++it) {
    
    const Light light = *it;

    RTColor Sj = _stracer->shadowFactor(point, &light);

    if (Sj < 0.000001) {
      continue;
    } 

    float fattj = computeFattj(&light);

    total += Sj * (diffuse(&light) + specular(&light)) * fattj;

   
  }

  return total;
}

RTColor WhittedIlluminator::diffuse(const Light *light) {

  Matrix N = -shape->normal(point, rayOrigin)->normalize();
  Matrix Dj = light->getDirectionFrom(point);
  
  float value = fmax(0, (-N).dot(Dj.normalize()));
  RTColor Cd = material.getDiffColor();
  float kt = material.getKTransparency();

  return Cd * (1.0f - kt)  * value;

}

RTColor WhittedIlluminator::specular(const Light *light) {

  Matrix V = (rayOrigin - point);
  Matrix L = light->getDirectionFrom(point);
  V.normalize();
  L.normalize();

  RTColor ks = material.getSpecColor();
  float q = material.getShininess() * 128;

  Matrix N = shape->normal(point, rayOrigin)->normalize();

  Matrix R = 2 * N.dot(L) * N - L;
  R.normalize();

  float x = R.dot(V);

  RTColor value = ks * pow(x > 0 ? x : 0, q);

  return value;
}

RTColor WhittedIlluminator::reflection() {
  
  RTColor ks = material.getSpecColor();
  
  if (ks < 0.000001) {
    return RTColor::BLACK;
  }

  if (_reflectionsComputed++ < REFLECTIONS) {

    Matrix L = rayOrigin - point;
    Matrix N = shape->normal(point, rayOrigin)->normalize();
    Matrix R = 2 * N.dot(L) * N - L;
    R.normalize();
    

    Ray ray(point + 0.00001*N, R);

    IntersectionPtr intersection = _scene->intersect(ray);

    if (intersection != nullptr) {
      WhittedIlluminator* illuminator = this->newIlluminator(_stracer,_scene);
      RTColor color = illuminator->illuminate(*intersection) * ks;
      delete illuminator;
      return color;
    }
    
  }

  return RTColor::BLACK;
}

bool WhittedIlluminator::isGoingIntoObject() {
  return rayDirection.dot(shape->normal(point, rayOrigin)->normalize()) > 0;
}

RTColor WhittedIlluminator::refraction() {


  float kt = material.getKTransparency();

  if (kt < 0.000001) {
    return RTColor::BLACK;
  }

  float n1, n2;
  if (isGoingIntoObject()) {
    n1 = (_refractionCount == 0) ? ETA1: ETA2;
    _refractionCount++;
  } else {
    n2 = (_refractionCount == 1) ? ETA2 : ETA1;
    _refractionCount--;
  }

  Matrix N = shape->normal(point, rayOrigin)->normalize();
  
  Matrix I = rayOrigin - point;

  //Matrix direction = Snell::direction(n1, n2, N, I);
  //direction.normalize();

  Ray inObject(point + N*0.000001, rayDirection);

  IntersectionPtr intersection = _scene->intersect(inObject);
  
  if (intersection != nullptr) {
    WhittedIlluminator* illuminator = this->newIlluminator(_stracer,_scene);
    RTColor color = illuminator->illuminate(*intersection) * kt;
    delete illuminator;
    return color;
  }
  
  return RTColor::BLACK;
}

float WhittedIlluminator::computeFattj(const Light *light) {
  
  if (light->getType() == POINT) {

    float distance = (light->getPosition() - point).length();

    float d = distance;
    float dd = d*d;

    return fmin( 1.0, 1.0 / C1 + C2*d +C3*dd );
  } else {
    return 1;
  }
}
