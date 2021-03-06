#include "ShadowTracer.h"

bool ShadowTracer::hasOcclusion(const Vector light,  const Vector* point) {

  Vector origin = light;
  Vector direction = (origin - *point);
  Vector normalized = direction.normalize();
  
  Ray lightRay(*point, normalized);

  IntersectionPtr intersection = _scene->intersect(lightRay);
  
  if (intersection != nullptr) {
    return fabs((*point - intersection->getPoint()).length()) > 0.001;
  } else {
    return false;
  }
  
}


std::vector<const Light*> ShadowTracer::getLightSources(const Vector *point) {
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

RTColor ShadowTracer::shadowFactor(const Vector &point, const Light *light) {

  RTColor color(1,1,1);

  Vector direction = light->getDirectionFrom(point);

  Ray ray(point, direction.normalize());

  
  IntersectionPtr intersection = _scene->intersect(ray);

  Vector L = light->getPosition();
  Vector P = point;

  if (intersection != nullptr && ((P-L).length() > (P-intersection->getPoint()).length())) {
    RTMaterial m = intersection->getShape()->getMaterial(0);
    float kt = m.getKTransparency();
    RTColor c = m.getDiffColor();
    return color * c.normalize() * kt;
  } else {
    return color;
  }
 

  std::vector<IntersectionPtr> intersections = _scene->intersections(ray);

  std::vector<IntersectionPtr>::iterator it;
  for (it = intersections.begin();
       it != intersections.end(); 
       ++it) {
    RTMaterial m = (*it)->getShape()->getMaterial(0);
    float kt = m.getKTransparency();
    RTColor c = m.getDiffColor();
    color = color * c.normalize() * kt;
  }

  return color;
}
