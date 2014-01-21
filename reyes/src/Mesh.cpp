#include "Mesh.h"

Mesh::Mesh() {

  this->_m = this->_n = 20;
  
  this->mesh = new Matrix[this->_m*this->_n];

  for (int i=0; i<_m *_n; i++) {
    this->mesh[i] = Matrix(4,1);
  }

}

Mesh::~Mesh() {
  
  delete [] this->mesh;

}

Matrix Mesh::getPoint(int i) {
  return this->mesh[i];
}

Mesh & Mesh::projectOnto(Matrix &projectionMatrix) {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[i] = projectionMatrix * this->mesh[i];
  }

  return *this;
  
}

Mesh & Mesh::transform(Matrix &transformMatrix) {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[i] = transformMatrix * this->mesh[i];
  }

  return * this;
}


Mesh & Mesh::homogenize() {
  
  for (int i=0; i<_m*_n; i++) {
    this->mesh[i].homogenize();
  }

  return *this;

}

BoundingBox Mesh::getBoundingBox() {

  float minx = this->mesh[0].get(0,0);
  float miny = this->mesh[0].get(1,0);
  float maxx = this->mesh[0].get(0,0);
  float maxy = this->mesh[0].get(1,0);
  
  for (int i=1; i<_m*_n; i++) {
    float x = this->mesh[i].get(0,0);
    float y = this->mesh[i].get(1,0);

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
    this->mesh[i].printPoint();
  }
  
}
