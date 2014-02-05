#include "RTPolySet.h"

void RTPolySet::addTriangle(RTTriangle &triangle) {
  triangles.push_back(triangle);
}

const RTTriangle RTPolySet::getTriangle(int i) const {
  return triangles[(size_t)i];
}

MatrixPtr RTPolySet::intersect(const Ray & ray) {

  std::vector<RTTriangle>::iterator it;
  for (it = triangles.begin();
       it != triangles.end();
       ++it) {
    if (it->intersect(ray)) {
      return MatrixPtr(new Matrix());
    }
  }
  return MatrixPtr(NULL);
}
