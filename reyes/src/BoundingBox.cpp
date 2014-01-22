#include "BoundingBox.h"

void BoundingBox::projectToScreen(int width, int height) {
  (void) height;
  this->_x = this->_x * width + width / 2;
  this->_y = this->_y * height + height / 2;
  this->_dx *= width;
  this->_dy *= height;

}

void BoundingBox::print() {

  printf("(%f, %f) + (%f %f)\n", _x, _y, _dx, _dy);
  
}

/*std::ostream & operator<<(std::ostream &out, const BoundingBox &rhs) {
  return out << "("
             << rhs._x << ", "
             << rhs._y << ", "
             << rhs._dx << ", "
             << rhs._dy << ")\n"; 
}
*/
