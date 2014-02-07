#include "WhittedIlluminator.h"

RTColor WhittedIlluminator::illuminate(IntersectionPtr intersection) {

  RTShape *shape = intersection->getShape();

  if (shape->getMaterialCount() == 0) {
    return RTColor::BLACK;
  }
  
  RTMaterial material = shape->getMaterial(0);
  Matrix p = intersection->getPoint();
  
  std::vector<const Light*> sources = _stracer->getLightSources(&p);
  if (sources.size() == 0) {
    return material.getAmbColor();
  } else {
    return material.getDiffColor();
  }

}
