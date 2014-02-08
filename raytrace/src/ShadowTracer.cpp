#include "ShadowTracer.h"

bool ShadowTracer::hasOcclusion(const Matrix light,  const Matrix* point) {

  Matrix origin = light;
  Matrix direction = (origin - *point);
  Matrix normalized = direction.normalize();
  
  Ray lightRay(*point, normalized);

  IntersectionPtr intersection = _scene->intersect(lightRay);
  
  if (intersection != nullptr) {
    return fabs((*point - intersection->getPoint()).length()) > 0.001;
  } else {
    return false;
  }
  
}

bool ShadowTracer::isInShadow(const Matrix* point) {

  LightIter it;
  for (it = _scene->lightsBegin();
       it != _scene->lightsEnd();
       ++it) {
    
    Matrix lightPosition = it->getPosition();

    switch (it->getType()) {
    case POINT: 
      lightPosition = it->getPosition();
      break;
    case DIRECTIONAL:
      lightPosition = *point + -100*it->getDirection();
      break;      
    }
   
    if (!hasOcclusion(lightPosition, point)) {
      return false;
    }
  }

  return true;
}

std::vector<const Light*> ShadowTracer::getLightSources(const Matrix *point) {
  (void) point;
  std::vector<const Light*> sources;

  LightIter it; (void) point;
  for (it = _scene->lightsBegin();
       it != _scene->lightsEnd();
       ++it) {
    
    if (!hasOcclusion(it->getPosition(), point)) {
      sources.push_back(&(*it));
    }
  }

  
  return sources;

}
