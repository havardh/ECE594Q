#include "ShadedWhittedIlluminator.h"
#include <assert.h>

WhittedIlluminator* newIlluminator(ShadowTracer *stracer, Scene *scene) {
  ShadedWhittedIlluminator* illuminator = new ShadedWhittedIlluminator(stracer, scene);
  assert(illuminator);
 
  return illuminator;
  
}

void ShadedWhittedIlluminator::setLocalVariables(Intersection intersection) {
  
  WhittedIlluminator::setLocalVariables(intersection);

  material = shape->shadePoint(point);

}
