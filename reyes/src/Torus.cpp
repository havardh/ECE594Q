#include "Torus.h"

Torus::Torus(float majorradius, float minorradius, float phimin, float phimax, float thetamax) {

  for (int u=0; u<_m; u++) {

    float theta = thetamax/(_m-1) * u;

    for (int v=0; v<_n; v++) {

      float phi = phimin + (v/(_n-1)) * (phimax - phimin);

      float r = (float)(minorradius * cos(phi));

      float x = (float)((majorradius + r) * cos(theta));
      float y = (float)((majorradius + r) * sin(theta));
      float z = (float)(minorradius * sin(phi));

      float values[] = { x, y, z, 1 };
      this->getPoint(u, v).setAll(values);

    }

  }

}
