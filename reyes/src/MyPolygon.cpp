#include "MyPolygon.h"

MyPolygon::MyPolygon() {

  this->_opacity = 1.0;
  
}

MyPolygon::MyPolygon(Matrix **points) {
  
  for (int i=0; i<4; i++) {
    this->_points[i] = points[i];
  }

  this->_opacity = 1.0;
  
}

Matrix * MyPolygon::get(int i) const {
  return this->_points[i];
} 

void MyPolygon::set(int i, Matrix * val) {
  this->_points[i] = val;
}

Color MyPolygon::getColor() const {
  return this->_color;
}

void MyPolygon::setColor(Color color) {
  this->_color = color;
}

BoundingBox MyPolygon::getBoundingBox() const {

  float minx = this->_points[0]->get(0);
  float miny = this->_points[0]->get(1);
  float maxx = this->_points[0]->get(0);
  float maxy = this->_points[0]->get(1);
  

  for (int i=1; i<4; i++) {
    float x = this->_points[i]->get(0);
    float y = this->_points[i]->get(1);

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

  if ( (x0 == x2 && y0 == y2) || (x1 == x2 && y1 == y2) )
    return 0.0f;

  float a0 = ( x0 * (y1 - y2) );
  float a1 = ( y0 * (x1 - x2) );
  float a2 = ( x1*y2 - x2*y1 );

  return a0 - a1 + a2;

}

float sign(float x0, float y0, float x1, float y1, float x2, float y2) {

  float f = ((x0 - x2) * (y1 - y2)) - ((x1 - x2) * (y0 - y2));
  return f;

}

bool isInTriangle(float x0, float y0, float x1, float y1, float x2, float y2, float x, float y) {

  //bool b0 = determinant(x0, y0, x1, y1, x, y) <= 0.0f;
  //bool b1 = determinant(x1, y1, x2, y2, x, y) <= 0.0f;
  //bool b2 = determinant(x2, y2, x0, y0, x, y) <= 0.0f;

  bool b0 = sign(x, y, x0, y0, x1, y1) < 0.0f;
  bool b1 = sign(x, y, x1, y1, x2, y2) < 0.0f;
  bool b2 = sign(x, y, x2, y2, x0, y0) < 0.0f;

  return ( (b0 == b1) && (b1 == b2) );

}

bool MyPolygon::intersects(float x, float y) {

  float x0 = this->_points[0]->get(0);
  float y0 = this->_points[0]->get(1);
  float x1 = this->_points[1]->get(0);
  float y1 = this->_points[1]->get(1);
  float x2 = this->_points[2]->get(0);
  float y2 = this->_points[2]->get(1);
  float x3 = this->_points[3]->get(0);
  float y3 = this->_points[3]->get(1);

  bool in0 = isInTriangle(x2,y2, x1,y1, x3,y3, x, y);
  bool in1 = isInTriangle(x1,y1, x0,y0, x2,y2, x, y);

  return in0 || in1;
}

Matrix MyPolygon::getSurfaceNormal() const {

  Matrix m1(
    get(1)->get(0) - get(0)->get(0),
    get(1)->get(1) - get(0)->get(1),
    get(1)->get(2) - get(0)->get(2),
    1
  );

  Matrix m2(
    get(2)->get(0) - get(0)->get(0),
    get(2)->get(1) - get(0)->get(1),
    get(2)->get(2) - get(0)->get(2),
    1
  );

  return m1.crossProduct(m2);

}
