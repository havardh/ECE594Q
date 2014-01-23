#include "SimplePolygon.h"

SimplePolygon::SimplePolygon(Micropolygon p) {

  for (int i=0; i<4; i++) {
    set(i, p.get(i));
  }

  simplify();

}


void SimplePolygon::simplify() {

  Matrix topLeft = *getTopLeft();
  Matrix rightTop = *getRightTop(topLeft);
  Matrix bottomRight = *getBottomRight(topLeft, rightTop);
  Matrix leftBottom = *getLeftBottom(topLeft, rightTop, bottomRight);

  set(0, topLeft);
  set(1, rightTop);
  set(2, bottomRight);
  set(3, leftBottom);

}

Matrix * SimplePolygon::getTopLeft() {
  int index = 0;

  for (int i=1; i<4; i++) {
    if (_points[i].get(1) > _points[index].get(1)
        || (_points[i].get(1) == _points[index].get(1) 
            && _points[i].get(0)  < _points[index].get(0))) {
      index = i;
    }
  }
  
  return &_points[index];
}

Matrix * SimplePolygon::getRightTop(Matrix ex1) {
  (void) ex1;
  int index = 0;

  for (int i=1; i<4; i++) {
    
      if (_points[i].get(0) > _points[index].get(0)
          || (_points[i].get(0) == _points[index].get(0)
              && _points[i].get(1) > _points[index].get(1))) {
        index = i;
      } 
  }
  
  return &_points[index];
}

Matrix * SimplePolygon::getBottomRight(Matrix ex1 ,Matrix ex2) {
  (void) ex1; (void) ex2;
  int index = 0;

  for (int i=1; i<4; i++) {
      if (_points[i].get(1) < _points[index].get(1) || 
          (_points[i].get(1) == _points[index].get(1) 
           && _points[i].get(0)  > _points[index].get(0))) {
        index = i;
      }
  }
  
  return &_points[index];
}

Matrix * SimplePolygon::getLeftBottom(Matrix ex1,Matrix ex2, Matrix ex3) {
  (void) ex1; (void) ex2; (void) ex3;
  int index = 0;

  for (int i=1; i<4; i++) {
      if (_points[i].get(0) < _points[index].get(0)
          || (_points[i].get(0) == _points[index].get(0)
              && _points[i].get(1) < _points[index].get(1))) {
        index = i;
      } 
  }
  
  return &_points[index];
}

