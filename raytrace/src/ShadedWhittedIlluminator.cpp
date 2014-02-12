#include "ShadedWhittedIlluminator.h"

WhittedIlluminator* newIlluminator(ShadowTracer *stracer, Scene *scene) {

  return new ShadedWhittedIlluminator(stracer, scene);
  
}

void ShadedWhittedIlluminator::setLocalVariables(Intersection intersection) {
  
  WhittedIlluminator::setLocalVariables(intersection);

  material = shape->shadePoint(point);

}
