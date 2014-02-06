#include "ShadowTracer.h"

bool ShadowTracer::hasOcclusion(const Matrix light,  const Matrix* point) {

  Matrix origin = light;
  Matrix direction = (origin - *point);
  Ray lightRay(origin, direction.normalize());
  
  return (_scene->intersect(lightRay) != nullptr);
  
}

bool ShadowTracer::isInShadow(const Matrix* point) {

  LightIter it; (void) point;
  for (it = _scene->lightsBegin();
       it != _scene->lightsEnd();
       ++it) {

    if (!hasOcclusion(it->getPosition(), point)) {
      return false;
    }
  }

  return true;
}
