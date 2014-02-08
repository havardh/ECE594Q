#include "WhittedIlluminator.h"

RTColor WhittedIlluminator::illuminate(Intersection intersection) {
  RTShape *shape = intersection.getShape();

  if (shape->getMaterialCount() == 0) {
    return RTColor::BLACK;
  }
  
  RTMaterial material = shape->getMaterial(0);
  Matrix p = intersection.getPoint();

  std::vector<const Light*> sources = _stracer->getLightSources(&p);
  if (sources.size() == 0) {
    return material.getAmbColor();
  } else {

    float f = 0;
    
    std::vector<const Light*>::iterator it;
    for (it = sources.begin();
         it != sources.end();
         ++it) {
      Matrix normal = *shape->normal(p, intersection.getRay().getOrigin());
      normal.normalize();
      Matrix distance = (p - (*it)->getPosition());
      distance.normalize();
    
      float v = -normal.dot(distance);
      f += (v > 0) ? v : 0;
    }

    RTColor color = material.getDiffColor();
    
    f = f > 1.0 ? 1.0 : f;
    return color * f;
  }
}
