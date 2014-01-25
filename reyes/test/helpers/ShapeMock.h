#ifndef _SHAPEMOCK_H_
#define _SHAPEMOCK_H_

#include "Shape.h"

class ShapeMock : public Shape {

public:
  ShapeMock(float * values, int m, int n) : Shape(m, n) {
    
    for (int i=0; i<m*n; i++) { 
      this->getPoint(i).setAll(&values[i*4]);
    }
  }
  
};

#endif /* _SHAPEMOCK_H_ */
