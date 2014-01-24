#include "Sphere.h"

Sphere::Sphere(float radius, float zmin, float zmax, float thetamax) {

  float phi_min = (float)(zmin > -radius ? asin(zmin/radius) : -M_PI / 4);
  float phi_max = (float)(zmax < radius ? asin(zmax/radius) : M_PI / 4);

  for (int u=0; u<_m; u++) {

    float theta = thetamax/(_m-1) * u;

    for (int v=0; v<_n; v++) {
      
      float phi = phi_min + (v / (float)_n) * (phi_max - phi_min);

      float x = radius * (float)(cos(theta) * cos(phi));
      float y = radius * (float)(sin(theta) * cos(phi));
      float z = radius * (float)(sin(phi));
      
      float values[] = { x, y, z, 1 };
      this->getPoint(u, v).setAll(values);

    }
  }
}
