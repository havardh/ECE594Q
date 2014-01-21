#ifndef _MICROPOLYGON_H_
#define _MICROPOLYGON_H_

#include "Matrix.h"

class Micropolygon {

private:
  Matrix _points[4];

  void allocate();
  
public:
  Micropolygon();
  Micropolygon(Matrix * points);

  Matrix get(int i) const;
  void set(int i, Matrix);
  
};

#endif /* _MICROPOLYGON_H_ */
