#include "Micropolygon.h"

Micropolygon::Micropolygon() {

  this->allocate();
  
}

Micropolygon::Micropolygon(Matrix *points) {
  
  for (int i=0; i<4; i++) {
    this->_points[i] = points[i];
  }
  
}

void Micropolygon::allocate() {

  for (int i=0; i<4; i++) {
    _points[i] = Matrix(4,1);
  }
}

Matrix Micropolygon::get(int i) const {
  return this->_points[i];
}

void Micropolygon::set(int i, Matrix val) {
  this->_points[i] = val;
}
