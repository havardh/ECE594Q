#include "Sphere.h"

Sphere::Sphere() : Mesh() {

  for (int i=0; i<_m; i++) {
    float iangle = (float)((M_PI / _m) * i);

    for (int j=0; j<_n; j++) {
      
      float jangle = (float)((2*M_PI / _n) * j);

      float x = (float)(cos(jangle) * sin(iangle));
      float y = (float)cos(iangle);
      float z = (float)(sin(jangle) * sin(iangle));
      
      float values[] = { x, y, z, 1 };
      this->mesh[ i*_m + j ].setAll(values);

    }
  }
}
