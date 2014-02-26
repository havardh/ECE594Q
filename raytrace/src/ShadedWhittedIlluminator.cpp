#include "ShadedWhittedIlluminator.h"
#include <assert.h>

WhittedIlluminator* ShadedWhittedIlluminator::newIlluminator(ShadowTracer *stracer, Scene *scene) {
  ShadedWhittedIlluminator* illuminator = new ShadedWhittedIlluminator(stracer, scene);
  assert(illuminator);
  illuminator->setReflectionsComputed(this->reflectionsComputed());
  illuminator->setRefractionCount(this->refractionCount()); 
  return illuminator;
  
}

void ShadedWhittedIlluminator::setLocalVariables(Intersection intersection) {
  
  WhittedIlluminator::setLocalVariables(intersection);

  material = shape->shadePoint(point);

}
