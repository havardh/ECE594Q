#include "Cone.h"

Cone::Cone(float height, float radius, float thetamax) {

  for (int u=0; u<_m; u++) {

    float theta = thetamax/_m * u;

    for (int v=0; v<_n; v++) {

      float x = radius * ((float)_n - v) / _n * cos(theta);
      float y = radius * ((float)_n - v) / _n * sin(theta);
      float z = ((float)v/ _n) * height;
      
      float values[] = {x,y,z,1};
      this->mesh[(size_t)(u*_m + v)].setAll(values);
    }
  }

}
