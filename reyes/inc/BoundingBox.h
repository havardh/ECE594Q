#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include <stdio.h>
#include <assert.h>

class BoundingBox {

public:
  BoundingBox(float x, float y, float dx, float dy) :  _x(x), _y(y), _dx(dx), _dy(dy) {}

  float getX() { return _x; }
  float getY() { return _y; }
  float getDX() { return _dx; }
  float getDY() { return _dy; }

  void projectToScreen(int, int);

  void print();
  
  //friend std::ostream & operator<<(std::ostream &, const BoundingBox &);
  
private:
  float _x, _y, _dx, _dy;
  
};

#endif /* _BOUNDINGBOX_H_ */
