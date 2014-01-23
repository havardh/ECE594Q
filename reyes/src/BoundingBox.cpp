#include "BoundingBox.h"

void BoundingBox::projectToScreen(int width, int height) {

  this->_x = (this->_x + 1.0f) / 2.0f * width;
  this->_y = (this->_y + 1.0f) / 2.0f * height;
  this->_dx *= width;
  this->_dy *= height;

  //assert(_x >= 0);
  //assert(_x < width);
  //assert(_y >= 0);
  //assert(_y < height);
  //assert(_x + _dx < width);
  //assert(_y + _dy < height);

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
