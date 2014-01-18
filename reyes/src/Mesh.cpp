#include "Mesh.h"

Mesh::Mesh() {

  this->_m = this->_n = 10;
  
  this->mesh = new MeshPoint[this->_m*this->_n];

}

Mesh::~Mesh() {

  delete [] this->mesh;

}
