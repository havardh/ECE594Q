#include "WhittedIlluminator.h"

#define C1 0.25f
#define C2 0.1f
#define C3 0.001f

RTColor WhittedIlluminator::illuminate(Intersection intersection) {
  RTShape *shape = intersection.getShape();

  if (shape->getMaterialCount() == 0) {
    return RTColor::BLACK;
  }
  
  RTMaterial material = shape->getMaterial(0);
  Matrix p = intersection.getPoint();

  std::vector<const Light*> sources = _stracer->getLightSources(&p);
  if (sources.size() == 0) {

    return material.getDiffColor() * 0.2f;

  } else {

    float f = 0;
    
    std::vector<const Light*>::iterator it;
    for (it = sources.begin();
         it != sources.end();
         ++it) {
      Matrix normal = *shape->normal(p, intersection.getRay().getOrigin());
      normal.normalize();
      Matrix distance = (p - (*it)->getPosition());
      float d = distance.length();
      distance.normalize();
    
      float v = -normal.dot(distance);
      if (v > 0) {
        float falloff = fmin( 1.0, 1.0 / C1 + C2*d +C3*d*d );
        f += v * falloff;
      }

    }

    RTColor color = material.getDiffColor();

    f = f > 1.0 ? 1.0 : f;
    return color * f * (1 - material.getKTransparency());
  }
}
