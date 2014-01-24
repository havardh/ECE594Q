#include "Mesh.h"


Mesh::Mesh(int m, int n) : _m(m), _n(n) {

  for (int i=0; i<_m *_n; i++) {
    MeshPoint p = { Matrix(4,1) };
    this->mesh.push_back(p);
  }

}

Matrix & Mesh::getPoint(int i) {
  return this->mesh[(size_t)i].point;
}

Matrix & Mesh::getPoint(int u, int v) {
  return getPoint( u * _n + v );
}

Mesh & Mesh::projectOnto(Matrix &projectionMatrix) {

  for (int i=0; i<_m*_n; i++) {
    getPoint(i) = projectionMatrix * getPoint(i);
  }

  return *this;
  
}

Mesh & Mesh::transform(Matrix &transformMatrix) {

  for (int i=0; i<_m*_n; i++) {
    getPoint(i) = transformMatrix * getPoint(i);
  }

  return * this;
}


Mesh & Mesh::homogenize() {
  
  for (int i=0; i<_m*_n; i++) {
    getPoint(i).homogenize();
  }

  return *this;

}

BoundingBox Mesh::getBoundingBox() {

  float minx = getPoint(0).get(0,0);
  float miny = getPoint(0).get(1,0);
  float maxx = getPoint(0).get(0,0);
  float maxy = getPoint(0).get(1,0);
  
  for (int i=1; i<_m*_n; i++) {
    float x = getPoint(i).get(0,0);
    float y = getPoint(i).get(1,0);

    if ( x > maxx )
      maxx = x;

    if ( y > maxy )
      maxy = y;

    if ( x < minx )
      minx = x;

    if ( y < miny )
      miny = y;
  }
  
  return BoundingBox(minx, miny, maxx-minx, maxy-miny);
  
}


void Mesh::printMesh() {

  for (int i=0; i<_m*_n; i++) {
    getPoint(i).printPoint();
  }
  
}
