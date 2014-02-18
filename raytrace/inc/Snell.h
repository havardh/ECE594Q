#ifndef _SNELL_H_
#define _SNELL_H_

#include "Vector.h"

class Snell {
public:
  static Vector direction(float n1, float n2, Vector N, Vector I);

};

#endif /* _SNELL_H_ */
