#include "RTPolySet.h"

void RTPolySet::addTriangle(RTTriangle &triangle) {
  triangles.push_back(triangle);
}

const RTTriangle RTPolySet::getTriangle(int i) const {
  return triangles[(size_t)i];
}

IntersectionPtr RTPolySet::intersect(const Ray ray) {

  std::vector<RTTriangle>::iterator it;
  for (it = triangles.begin();
       it != triangles.end();
       ++it) {
    IntersectionPtr intersection = it->intersect(ray);
    if (intersection != nullptr) {
      return intersection;
    }
  }
  return IntersectionPtr(NULL);
}
MatrixPtr RTPolySet::normal(const Matrix &point, const Matrix &from) {
  (void) point; (void) from;
  return MatrixPtr(NULL);
}
