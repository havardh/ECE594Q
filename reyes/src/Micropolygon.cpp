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

BoundingBox Micropolygon::getBoundingBox() const {

  float minx = this->_points[0].get(0);
  float miny = this->_points[0].get(1);
  float maxx = this->_points[0].get(0);
  float maxy = this->_points[0].get(1);
  
  for (int i=1; i<4; i++) {
    float x = this->_points[i].get(0);
    float y = this->_points[i].get(1);

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
