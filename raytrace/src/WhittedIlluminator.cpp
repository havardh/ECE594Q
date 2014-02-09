#include "WhittedIlluminator.h"

#define C1 0.25f
#define C2 0.1f
#define C3 0.001f
#define REFLECTIONS 10
#define ETA1 1.0
#define ETA2 2.0


RTColor WhittedIlluminator::illuminate(Intersection intersection) {
  setShape(intersection.getShape());
  setMaterial(shape->getMaterial(0));
  setPoint(intersection.getPoint());
  setLightSources(_stracer->getLightSources(&point));
  setRayDirection(intersection.getRay().getDirection());
  setRayOrigin(intersection.getRay().getOrigin());
  //DPRINTF("\n");
  return ambient() + 
    direct() + 
    reflection() + 
    refraction()
    ;
}

RTColor WhittedIlluminator::ambient() {
  return material.getDiffColor() * 0.2f;
}

RTColor WhittedIlluminator::direct() {

  RTColor total;

  std::vector<const Light*>::iterator it;
  for (it = lightSources.begin(); it != lightSources.end(); ++it) {
    const Light *light = *it;

    float fattj = computeFattj(light);

    total += (diffuse(light) + specular(light)) * fattj;

   
  }

  return total;
}

RTColor WhittedIlluminator::diffuse(const Light *light) {

  Matrix N = shape->normal(point, rayOrigin)->normalize();
  Matrix Dj = light->getPosition() - point;
  
  float value = fmax(0, N.dot(Dj.normalize()));
  RTColor Cd = material.getDiffColor();
  float kt = material.getKTransparency();

  return Cd * (1.0f - kt)  * value;

}

RTColor WhittedIlluminator::specular(const Light *light) {


  Matrix V = (rayOrigin - point);
  Matrix L = light->getPosition() - point;
  V.normalize();
  L.normalize();

  RTColor ks = material.getSpecColor();
  float q = material.getShininess() * 99999999;

  Matrix N = shape->normal(point, rayOrigin)->normalize();

  Matrix R = 2 * N.dot(L) * N - L;
  R.normalize();

  RTColor value = ks * pow(R.dot(V), q);

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
    Matrix R = 2* N.dot(L) * N - L;
    R.normalize();
    
    Ray ray(point, R);

    IntersectionPtr intersection = _scene->intersect(ray);

    if (intersection != nullptr) {
      return ks*illuminate(*intersection);
    }
    
  }

  return RTColor::BLACK;
}

RTColor WhittedIlluminator::refraction() {
  
  Matrix inObjectDirection = rayDirection;
  Matrix N = shape->normal(point, rayOrigin)->normalize();
  Ray inObject(point + N*0.000001, rayDirection);

  float kt = material.getKTransparency();

  if (kt < 0.000001) {
    return RTColor::BLACK;
  }

  IntersectionPtr outIntersection = _scene->intersect(inObject);
  
  if (outIntersection != nullptr) {
    
    //DPRINTF("DIR"); rayDirection.printPoint();

    Matrix outPoint = outIntersection->getPoint();
    Matrix outDirection = rayDirection;
    
    Ray outRay(outPoint + N*0.001, outDirection);
    

    
    IntersectionPtr intersection = _scene->intersect(outRay);

    if (intersection != nullptr) {
      //DPRINTF("ORIGIN"); rayOrigin.printPoint();
      //DPRINTF("INTERSECTION"); point.printPoint();
      //DPRINTF("OUTPOINT"); outPoint.printPoint();
          
      return illuminate(*intersection) * kt;
    }
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
