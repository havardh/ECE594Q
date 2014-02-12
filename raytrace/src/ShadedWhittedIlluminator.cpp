#include "ShadedWhittedIlluminator.h"

ShadedWhittedIlluminator::ShadedWhittedIlluminator(
  ShadowTracer *stracer, Scene *scene) : 
  WhittedIlluminator(stracer, scene) {

  material = shape->shadePoint(point);

}

WhittedIlluminator* newIlluminator(ShadowTracer *stracer, Scene *scene) {

  return new ShadedWhittedIlluminator(stracer, scene);
  
}
