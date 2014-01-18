#include "Sphere.h"

Sphere::Sphere() {


  for (int i=0; i<_m; i++) {
    float iangle = (float)((M_PI / _m) * i);

    for (int j=0; j<_n; j++) {
      
      float jangle = (float)((2*M_PI / _n) * j);

      float x = (float)(cos(jangle) * sin(iangle));
      float y = (float)cos(iangle);
      float z = (float)(sin(jangle) * sin(iangle));
      
      float values[] = { x, y, z };
      this->mesh[ i*_m + j ].point.setAll(values);

      //printf("(%2.2f, %2.2f, %2.2f)\n", x, y, z);

    }
  }

}
