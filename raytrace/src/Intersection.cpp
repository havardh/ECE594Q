#include "Intersection.h"

bool Intersection::operator<(const Intersection &rhs) const {

  float thisLength = (getRay().getOrigin() - getPoint()).length();
  float rhsLength = (rhs.getRay().getOrigin() - rhs.getPoint()).length();

  return thisLength < rhsLength;

}
