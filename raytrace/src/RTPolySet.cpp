#include "RTPolySet.h"

void RTPolySet::addTriangle(RTTriangle &triangle) {
  triangles.push_back(triangle);
}

const RTTriangle RTPolySet::getTriangle(int i) const {
  return triangles[(size_t)i];
}

bool RTPolySet::intersect(const Ray & ray) {

  std::vector<RTTriangle>::iterator it;
  for (it = triangles.begin();
       it != triangles.end();
       ++it) {
    if (it->intersect(ray)) {
      return true;
    }
  }
  return false;
}
