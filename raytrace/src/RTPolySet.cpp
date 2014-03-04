#include "RTPolySet.h"

void RTPolySet::addTriangle(RTTriangle triangle) {
  triangles.push_back(triangle);
}

const RTTriangle RTPolySet::getTriangle(int i) const {
  return triangles[(size_t)i];
}

RTTriangle* RTPolySet::getTrianglePointer(int i) {
  return &triangles[(size_t)i];
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

  printf("%lu\n", triangles.size());
}

// Duplicate of Scene::intersection should be refactored
IntersectionPtr RTPolySet::intersect(const Ray ray) {

  IntersectionPtr intersection(NULL);

  float min, max;
  if (!getBoundingBox().intersects(ray, min, max)) {
    DPRINTF("%lu\n", triangles.size());
    return intersection;
  }

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

VectorPtr RTPolySet::normal(const Vector &point) {
  (void) point;
  return VectorPtr(NULL);
}

void RTPolySet::interpolateUV(float &u, float &v, const Vector point) {
  (void) point;
  u = 0;
  v = 0;
}

const RTMaterial RTPolySet::interpolateMaterial(const Vector &point) {
  (void) point;
  return getMaterial(0);
}

BoundingBox RTPolySet::getBoundingBox() {
  if (!box) {

    BoundingBox b;

    // TODO: compiler error on iterator?
    for (int i=0; i<triangles.size(); i++) {
      
      RTTriangle triangle = triangles[i];
      
      b = b.unionWith(triangle.getBoundingBox());
      
    }

    box = new BoundingBox(b);

  }

  return *box;
}
