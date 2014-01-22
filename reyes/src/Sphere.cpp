#include "Sphere.h"

Sphere::Sphere(float radius) : Mesh(20,20) {

  for (int i=0; i<_m; i++) {
    float iangle = (float)((M_PI / _m) * i);

    for (int j=0; j<_n; j++) {
      
      float jangle = (float)((2*M_PI / _n) * j);

      float x = radius * (float)(cos(jangle) * sin(iangle));
      float y = radius * (float)cos(iangle);
      float z = radius * (float)(sin(jangle) * sin(iangle));
      
      float values[] = { x, y, z, 1 };
      this->mesh[ (size_t)(i*_m + j) ].setAll(values);

    }
  }
}
