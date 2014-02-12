#include "RTPolySet.h"

void RTPolySet::addTriangle(RTTriangle &triangle) {
  triangles.push_back(triangle);
}

const RTTriangle RTPolySet::getTriangle(int i) const {
  return triangles[(size_t)i];
}

void RTPolySet::calculateMidpoint() {

  std::vector<RTTriangle>::iterator it;
  for (it = triangles.begin(); 
       it != triangles.end(); 
       ++it) {
    
    midpoint = midpoint + it->getP0();
    midpoint = midpoint + it->getP1();
    midpoint = midpoint + it->getP2();

  }

  midpoint = midpoint * (1.0 / (triangles.size()*3));

}

// Duplicate of Scene::intersection should be refactored
IntersectionPtr RTPolySet::intersect(const Ray ray) {

  IntersectionPtr intersection(NULL);

  std::vector<RTTriangle>::iterator it;
  for (it = triangles.begin();
       it != triangles.end();
       ++it) {

    IntersectionPtr newIntersection = it->intersect(ray);
    if (newIntersection != nullptr) {
      if (intersection == nullptr || *newIntersection < *intersection) {
        intersection = newIntersection;
      }
    }
  }
  return intersection;
}

MatrixPtr RTPolySet::normal(const Matrix &point) {
  (void) point;
  return MatrixPtr(NULL);
}


RTMaterial RTPolySet::shadePoint(const Matrix &point) {
 (void) point;

  return RTMaterial();
}
