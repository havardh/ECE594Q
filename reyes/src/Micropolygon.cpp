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

float determinant(float x0, float y0, float x1, float y1, float x2, float y2) {

  float a0 = ( x0 * (y1 - y2) );
  float a1 = ( y0 * (x1 - x2) );
  float a2 = ( x1*y2 - x2*y1 );

  return a0 - a1 + a2;

}

bool isInTriangle(float x0, float y0, float x1, float y1, float x2, float y2, float x, float y) {

  bool b0 = determinant(x0, y0, x1, y1, x, y) <= 0.0f;
  bool b1 = determinant(x1, y1, x2, y2, x, y) <= 0.0f;
  bool b2 = determinant(x2, y2, x0, y0, x, y) <= 0.0f;

  return ( (b0 == b1) && (b1 == b2) );

}

bool Micropolygon::intersects(float x, float y) {

  float x0 = this->_points[0].get(0);
  float y0 = this->_points[0].get(1);
  float x1 = this->_points[1].get(0);
  float y1 = this->_points[1].get(1);
  float x2 = this->_points[2].get(0);
  float y2 = this->_points[2].get(1);
  float x3 = this->_points[3].get(0);
  float y3 = this->_points[3].get(1);
  
  bool in0 = isInTriangle(x0,y0, x1,y1, x2,y2, x, y);
  bool in1 = isInTriangle(x2,y2, x3,y3, x1,y1, x, y);

  return in0 || in1;
}
