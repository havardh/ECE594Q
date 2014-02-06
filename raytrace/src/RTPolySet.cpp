#include "RTPolySet.h"

void RTPolySet::addTriangle(RTTriangle &triangle) {
  triangles.push_back(triangle);
}

const RTTriangle RTPolySet::getTriangle(int i) const {
  return triangles[(size_t)i];
}

MatrixPtr RTPolySet::intersect(const Ray ray) {

  std::vector<RTTriangle>::iterator it;
  for (it = triangles.begin();
       it != triangles.end();
       ++it) {
    MatrixPtr intersection = it->intersect(ray);
    if (intersection != nullptr) {
      return MatrixPtr(new Matrix(0,0,0));
    }
  }
  return MatrixPtr(NULL);
}
MatrixPtr RTPolySet::normal(const Matrix &point, const Matrix &from) {
  (void) point; (void) from;
  return MatrixPtr(NULL);
}
