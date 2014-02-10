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

float ShadowTracer::shadowFactor(const Matrix &point, const Light *light) {

  float r = 1.0;

  Matrix direction = light->getDirectionFrom(point);

  Ray ray(point, direction.normalize());

  std::vector<IntersectionPtr> intersections = _scene->intersections(ray);

  std::vector<IntersectionPtr>::iterator it;
  for (it = intersections.begin();
       it != intersections.end(); 
       ++it) {
    RTMaterial m = (*it)->getShape()->getMaterial(0);
    r *= m.getKTransparency();
  }

  return r;
}
