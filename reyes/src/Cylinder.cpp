#include "Cylinder.h"

Cylinder::Cylinder(float radius, float zmin, float zmax, float thetamax) {

  for (int u=0; u<_m; u++) {

    float theta = thetamax/(_m-1) * u;
    
    for (int v=0; v<_n; v++) {

      float x = (float)(radius * cos(theta));
      float y = (float)(radius * sin(theta));
      float z = v/(float)(_n-1) * (zmax - zmin);

      float values[] = {x,y,z,1};
      this->getPoint(u, v).setAll(values);

    }
  }

}
