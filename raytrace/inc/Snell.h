#ifndef _SNELL_H_
#define _SNELL_H_

#include "Matrix.h"

class Snell {
public:
  static Matrix direction(float n1, float n2, Matrix N, Matrix I);

};

#endif /* _SNELL_H_ */
