#include "RenderVector.h"
#ifndef CPPUTEST
#include <fstream>
#endif

void renderRays() {

  RiBegin(RI_NULL);

  RiFormat(200, 200, 1.0);
  RiFrameAspectRatio(1.0);

  float fov = 45.0;
  RiProjection(RI_PERSPECTIVE, "fov", &fov);

  RiFrameBegin(0);
  RiWorldBegin();

  renderVectors();

  RiWorldEnd();
  RiFrameEnd();
  RiEnd();

}

int readVector(float *V) {
  (void) V;
  #ifdef CPPUTEST
  return 0;
  #else
  std::ifstream infile("vec.out");
   
  float x, y, z;
  int i=0;
  while(infile >> x >> y >> z) {
    V[i*6+0] = 0; V[i*6+1] = 0; V[i*6+2] = 0;
    V[i*6+3] = x; V[i*6+4] = y; V[i*6+5] = z;
    printf("...\n");
    i++;
    }

    infile.close();
  
  return i;
  #endif
}

void renderVectors() {
  
  float *V = new float[6 * 100];
  int n = readVector(V);

  for (int i=0; i < n; i++) {

    float O[] = { V[0+i*6], V[1+i*6], V[2+i*6] };
    float D[] = { V[3+i*6], V[4+i*6], V[5+i*6] };

    float x = D[0], y = D[1], z = D[2];
    (void) x;
    printf("%2.2f %2.2f %2.2f\n", O[0], O[1], O[2]);
    printf("%2.2f %2.2f %2.2f\n", D[0], D[1], D[2]);

    float ya = (float)asin(z / sqrt(1 + y*y));
    float za = (float)atan(y / sqrt(1 + y*y));
    
    printf("%f\n", ya);
    printf("%f\n", za);

    RiIdentity();
    RiRotate(-90, 0, 1, 0);
    RiRotate((float)((ya/(2*M_PI)) * 360.0), 0, 1, 0);
    RiRotate((float)((za/(2*M_PI)) * 360.0), 0, 0, 1);
    RiTranslate(0, 0, 30);
    RiCylinder(0.1f, 0, 10, 360, RI_NULL);

  }
}
