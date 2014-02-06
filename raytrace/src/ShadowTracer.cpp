#include "ShadowTracer.h"

bool ShadowTracer::hasOcclusion(Light *light,  Matrix* point) {

  Matrix origin = light->getPosition();
  Matrix direction = (origin - *point);
  Ray lightRay(origin, direction.normalize());

  return (_scene->intersect(lightRay) != nullptr);
  
}
