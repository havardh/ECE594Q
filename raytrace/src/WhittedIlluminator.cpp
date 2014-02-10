#include "WhittedIlluminator.h"

// Constants used for computing light falloff
#define C1 0.25f
#define C2 0.1f
#define C3 0.001f

// How many recursive steps in reflection
#define REFLECTIONS 1

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
    //refraction() +
    0;
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

    float Sj = _stracer->shadowFactor(point, &light);

    if (Sj < 0.000001) {
      continue;
    } 

    float fattj = computeFattj(&light);

    total += (diffuse(&light) + specular(&light)) * fattj * Sj;

   
  }

  return total;
}

RTColor WhittedIlluminator::diffuse(const Light *light) {

  Matrix N = -shape->normal(point, rayOrigin)->normalize();
  Matrix Dj;
  if (light->getType() == POINT) {
    Dj = light->getPosition() - point;
  } else {
    Dj = light->getDirection() * -1;
  }
  
  float value = fmax(0, (-N).dot(Dj.normalize()));
  RTColor Cd = material.getDiffColor();
  float kt = material.getKTransparency();

  return Cd * (1.0f - kt)  * value;

}

RTColor WhittedIlluminator::specular(const Light *light) {

  Matrix V = (rayOrigin - point);
  Matrix L;
  if (light->getType() == POINT) {
    L = light->getPosition() - point;
  } else {
    L = light->getDirection() * -1;
  } 
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
    

    Ray ray(point, R);

    IntersectionPtr intersection = _scene->intersect(ray);


    if (intersection != nullptr) {

      WhittedIlluminator illuminator(_stracer, _scene);
      RTColor color = ks * illuminator.illuminate(*intersection);
      return color;
    }
    
  }

  return RTColor::BLACK;
}

RTColor WhittedIlluminator::refraction() {

  float kt = material.getKTransparency();

  if (kt < 0.000001) {
    return RTColor::BLACK;
  }
  
  Matrix inObjectDirection = rayDirection;
  Matrix N = shape->normal(point, rayOrigin)->normalize();
  Ray inObject(point + N*0.000001, rayDirection);

  IntersectionPtr intersection = _scene->intersect(inObject);
  
  if (intersection != nullptr) {
    WhittedIlluminator illuminator(_stracer, _scene);
    return illuminator.illuminate(*intersection) * kt;
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
