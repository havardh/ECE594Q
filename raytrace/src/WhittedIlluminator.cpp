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

    Matrix normal = *shape->normal(p, intersection.getRay().getOrigin());
    normal.normalize();
    Matrix distance = (p - sources[0]->getPosition());
    distance.normalize();
    float f = normal.dot(distance);
    RTColor color = material.getDiffColor();


    return color * fabs(f);
  }

  return RTColor::BLACK;
}
