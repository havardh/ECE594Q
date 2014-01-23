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
  //transformMatrix.rotate(X, M_PI/4);
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
      float x = it->get(0).get(0);
      float y = it->get(0).get(1);
      //if (x < 0.03 && x > -0.01 && y < 0.03 && y > -0.01) {
        fb.drawMicropolygon(*it);
        //}
    }
  
    //fb.draw(&s);
    fb.flush(i);
  }

  return 0;
}
