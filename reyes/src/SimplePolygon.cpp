#include "SimplePolygon.h"

SimplePolygon::SimplePolygon(Micropolygon p) {

  for (int i=0; i<4; i++) {
    set(i, p.get(i));
  }

  simplify();

}


void SimplePolygon::simplify() {

  Matrix topLeft = *getTopLeft();
  Matrix rightTop = *getRightTop();
  Matrix bottomRight = *getBottomRight();
  Matrix leftBottom = *getLeftBottom();

  set(0, topLeft);
  set(1, rightTop);
  set(2, bottomRight);
  set(3, leftBottom);

}

Matrix * SimplePolygon::getTopLeft() {
  int index = 0;

  for (int i=1; i<4; i++) {
    if (_points[i].get(1) > _points[index].get(1)) {
      index = i;
    } else if (_points[i].get(1) == _points[index].get(1) 
               && _points[i].get(0)  < _points[index].get(0)) {
      index = i;
    }
  }
  
  return &_points[index];
}

Matrix * SimplePolygon::getRightTop() {
  int index = 0;

  for (int i=1; i<4; i++) {
    if (_points[i].get(0) > _points[index].get(0)) {
      index = i;
    } else if (_points[i].get(0) == _points[index].get(0)
               && _points[i].get(1) > _points[index].get(1)) {
      index = i;
    } 
  }
  
  return &_points[index];
}

Matrix * SimplePolygon::getBottomRight() {
    int index = 0;

  for (int i=1; i<4; i++) {
    if (_points[i].get(1) < _points[index].get(1)) {
      index = i;
    } else if (_points[i].get(1) == _points[index].get(1)
               && _points[i].get(0)  > _points[index].get(0)) {
      index = i;
    }
  }
  
  return &_points[index];
}

Matrix * SimplePolygon::getLeftBottom() {

  int index = 0;

  for (int i=1; i<4; i++) {
    if (_points[i].get(0) < _points[index].get(0)) {
      index = i;
    } else if (_points[i].get(0) == _points[index].get(0)
               && _points[i].get(1) < _points[index].get(1)) {
      index = i;
    } 
  }
  
  return &_points[index];
}

