#include "WhittedIlluminator.h"
#include <assert.h>


// How many recursive steps in reflection
#define REFLECTIONS 10

#define ETA1 1.0 // refraction index for air
#define ETA2 1.5 // refraction index for solid object


RTColor WhittedIlluminator::illuminate(Intersection intersection) {
  assert(this);
  setLocalVariables(intersection);

  return ambient() + 
    direct() + 
    reflection() + 
    //refraction() +
    0;
}

void WhittedIlluminator::setLocalVariables(Intersection intersection) {
  Illuminator::setLocalVariables(intersection);
}

WhittedIlluminator* WhittedIlluminator::newIlluminator(
  ShadowTracer *shadowTracer, Scene *scene) {
  WhittedIlluminator* illuminator = new WhittedIlluminator();
  illuminator->setShadowTracer(shadowTracer);
  illuminator->setScene(scene);
  illuminator->setReflectionsComputed(reflectionsComputed());
  illuminator->setRefractionCount(refractionCount());
  return illuminator;
}

RTColor WhittedIlluminator::ambient() {
  return Illuminator::ambient();
}

RTColor WhittedIlluminator::direct() {

  RTColor total;

  LightIter it;
  
  if (!getScene()) return RTColor::BLACK;

  
  for (it = getScene()->lightsBegin(); it != getScene()->lightsEnd(); ++it) {
    
    const Light light = *it;

    Vector N = *shape->normal(point);
    
    RTColor Sj = getShadowTracer()->shadowFactor(point + N*0.0001, &light);

    if (Sj < 0.000001) {
      continue;
    } 

    float fattj = computeFattj(&light);
    
    if (fattj > 0) {
      total += Sj * (diffuse(&light) + specular(&light)) * fattj;
    }
   
  }

  return total;
}

RTColor WhittedIlluminator::diffuse(const Light *light) {

  return Illuminator::diffuse(light);

}

RTColor WhittedIlluminator::specular(const Light *light) {

  return Illuminator::specular(light);
}

RTColor WhittedIlluminator::reflection() {
  
  RTColor ks = material.getSpecColor();

  if (refractionCount() > 0) {
    return RTColor::BLACK;
  }

  if (ks < 0.000001) {
    return RTColor::BLACK;
  }

  if (incrementReflectionComputed() < REFLECTIONS) {

    Vector L = rayOrigin - point;
    Vector N = shape->normal(point)->normalize();
    Vector R = 2 * N.dot(L) * N - L;
    R.normalize();

    Ray ray(point + 0.00001*N, R);

    IntersectionPtr intersection = getScene()->intersect(ray);

    if (intersection != nullptr) {
      WhittedIlluminator* illuminator = this->newIlluminator(
        getShadowTracer(), getScene());
      assert(illuminator);
      RTColor color = illuminator->illuminate(*intersection) * ks;
      delete illuminator;
      return color;
    }
    
  }

  return RTColor::BLACK;
}

bool WhittedIlluminator::isGoingIntoObject() {
  Vector N = shape->normal(point)->normalize();

  return rayDirection.dot(N) < 0;
}

RTColor WhittedIlluminator::refraction() {


  float kt = material.getKTransparency();

  if (kt < 0.000001) {
    return RTColor::BLACK;
  }

  float n1, n2; bool isGoingIn;
  if (isGoingIntoObject()) {
    isGoingIn = true;
    DPRINTF("Going in\n");
    n1 = ETA1;
    n2 = ETA2;
    incrementRefractionCount();
  } else {
    isGoingIn = false;
    DPRINTF("Going out\n");
    n1 = ETA2;
    n2 = ETA1;
    decrementRefractionCount();
  }

  Vector N = shape->normal(point)->normalize();
  
  Vector I = (rayOrigin - point).normalize();
  Vector D = Snell::direction(n1,n2, N, I);

  if (D == Vector(0,0,0)) {
    return RTColor::BLACK;
  }

  Vector delta;
  if (isGoingIn) {
    delta = -N*0.000005;
  } else {
    delta = N*0.000005;
  }

  Ray inObject(point + N*0.01 , rayDirection);

  IntersectionPtr intersection = getScene()->intersect(inObject);

  if (intersection != nullptr) {

    WhittedIlluminator* illuminator = this->newIlluminator(
      getShadowTracer(), getScene());
    assert(illuminator);
    RTColor color = illuminator->illuminate(*intersection) * kt;
    delete illuminator;
    return color;
  }
  
  return RTColor::BLACK;
}
