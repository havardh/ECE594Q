#include "Mesh.h"

#define IX(row, col) ((row) * _n + (col))

Mesh::Mesh(int m, int n) : _m(m), _n(n) {

  for (int i=0; i<_m *_n; i++) {
    this->mesh.push_back(Matrix(4,1));
  }

}

Matrix Mesh::getPoint(int i) {
  return this->mesh[(size_t)i];
}

Mesh & Mesh::projectOnto(Matrix &projectionMatrix) {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[(size_t)i] = projectionMatrix * this->mesh[(size_t)i];
  }

  return *this;
  
}

Mesh & Mesh::transform(Matrix &transformMatrix) {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[(size_t)i] = transformMatrix * this->mesh[(size_t)i];
  }

  return * this;
}


Mesh & Mesh::homogenize() {
  
  for (int i=0; i<_m*_n; i++) {
    this->mesh[(size_t)i].homogenize();
  }

  return *this;

}

BoundingBox Mesh::getBoundingBox() {

  float minx = this->mesh[0].get(0,0);
  float miny = this->mesh[0].get(1,0);
  float maxx = this->mesh[0].get(0,0);
  float maxy = this->mesh[0].get(1,0);
  
  for (int i=1; i<_m*_n; i++) {
    float x = this->mesh[(size_t)i].get(0,0);
    float y = this->mesh[(size_t)i].get(1,0);

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
    this->mesh[(size_t)i].printPoint();
  }
  
}
