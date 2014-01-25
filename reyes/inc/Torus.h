#ifndef _TORUS_H_
#define _TORUS_H_

#include "Shape.h"

class Torus : public Shape {

public:
  Torus(float majorradius, float minorradius, float phimin, float phimax, float thetamax);

};

#endif /* _TORUS_H_ */
