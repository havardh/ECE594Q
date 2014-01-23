#include <stdio.h>
#include "Matrix.h"
#include "MatrixFactory.h"
#include "FrameBuffer.h"
#include "Sphere.h"
#include <cmath>
#include <iostream>
#include <vector>

#define WIDTH 640
#define HEIGHT 640
#define N 8

Matrix projectionMatrix = MatrixFactory::createPerspectiveProjection(
  M_PI/3, 
  4.0f/4.0f,
  1,
  1000
);

int main(int argc, char *argv[]) {
  
  Matrix translationVector(10, 0, 10);
  Matrix scaleVector(1, 1, 2);

  Sphere sphere(1);
  Matrix transformMatrix = MatrixFactory::createIdentity(4);
  transformMatrix.scale(10, 10, 10);
  transformMatrix.translate(0, 0, 100);
  sphere.transform(transformMatrix);
  
  FrameBuffer fb(WIDTH, HEIGHT);
  
  for (int i=0; i<1; i++) {
    
    Sphere s = sphere;

    s.projectOnto(projectionMatrix);
    s.homogenize();
    std::vector<Micropolygon> polygons = s.getMicropolygons();
  
    std::vector<Micropolygon>::iterator it;
    for (it = polygons.begin(); it != polygons.end(); ++it) {
      fb.drawMicropolygon(*it);
    }
  
    fb.flush(i);
  }

  return 0;
}
