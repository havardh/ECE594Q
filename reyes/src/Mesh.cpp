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

void Mesh::printMesh() {

  for (int i=0; i<_m*_n; i++) {
    this->mesh[i].printPoint();
  }
  
}
