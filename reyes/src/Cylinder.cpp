#include "Cylinder.h"

Cylinder::Cylinder(float radius, float zmin, float zmax, float thetamax) {

  for (int u=0; u<_m; u++) {

    float theta = thetamax/_m * u;
    
    for (int v=0; v<_n; v++) {

      float x = (float)(radius * cos(theta));
      float y = (float)(radius * sin(theta));
      float z = v/(float)_n * (zmax - zmin);

      float values[] = {x,y,z,1};
      this->mesh[(size_t)(u*_m + v)].setAll(values);

    }
  }

}
