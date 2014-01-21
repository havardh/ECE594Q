#include "BoundingBox.h"

void foo() {}

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
