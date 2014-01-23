#ifndef _SIMPLEPOLYGON_H_
#define _SIMPLEPOLYGON_H_

#include "Micropolygon.h"

class SimplePolygon : public Micropolygon {

public:
  SimplePolygon(Micropolygon);

private:
  void simplify();
  Matrix * getTopLeft();
  Matrix * getRightTop(Matrix);
  Matrix * getBottomRight(Matrix,Matrix);
  Matrix * getLeftBottom(Matrix,Matrix,Matrix);
  

};

#endif /* _SIMPLEPOLYGON_H_ */
