#include "PathTracerIlluminator.h"

// How many recursive steps in reflection
#define REFLECTIONS 2

static int light[3];

void printLightStats(void) {
  
  DPRINTF("0: %d\n", light[0]);
  DPRINTF("1: %d\n", light[1]);
  DPRINTF("2: %d\n", light[2]);

}

RTColor PathTracerIlluminator::illuminate(Intersection intersection) {
  setLocalVariables(intersection);
  
  int n = 1000;

  RTColor color;
  for (int i=0; i<n; i++) {
    color += direct() * (2.0/n); 
    color += reflection() * (1/10.0);
  }

  return color;

}

Illuminator* PathTracerIlluminator::newIlluminator(ShadowTracer *shadowTracer, Scene *scene) {
  Illuminator* illuminator =  new PathTracerIlluminator();
  illuminator->setShadowTracer(shadowTracer);
  illuminator->setScene(scene);
  illuminator->setReflectionsComputed(reflectionsComputed());
  illuminator->setRefractionCount(refractionCount());
  return illuminator;
}

RTColor PathTracerIlluminator::direct() {

  ShadowTracer *stracer = getShadowTracer();
  Vector N = *shape->normal(point);
  const Light *light = uniformlyRandomLightSource();
  RTColor Sj =  stracer->shadowFactor(point + N*0.0001, light);
  float fattj = computeFattj(light);
  return Sj * diffuse(light) * light->getColor() * fattj;

}

RTColor PathTracerIlluminator::reflection() {

  if (incrementReflectionComputed() < REFLECTIONS) {
    Illuminator* illuminator = this->newIlluminator(
      getShadowTracer(), getScene()
    );

    Intersection I = getIntersection();
    Ray path = PathFactory::createPath(I);
    
    IntersectionPtr intersection = getScene()->intersect(path);
    if (intersection != nullptr) {

      RTColor color = illuminator->illuminate(*intersection);
      delete illuminator;

      return color * 0.05;
    }
    
  }

  return RTColor(0,0,0);
}

RTColor PathTracerIlluminator::refraction() {
  return RTColor(0,0,0);
}



const Light* PathTracerIlluminator::uniformlyRandomLightSource() {

  Scene *scene = getScene();

  int n = scene->numLights();

  int i = rand() % n;
  light[i]++;

  LightIter lights = scene->lightsBegin();

  return &(lights[i]);
  
}
