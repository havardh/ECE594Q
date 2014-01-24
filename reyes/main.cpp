#include <stdio.h>
#include "Matrix.h"
#include "MatrixFactory.h"
#include "FrameBuffer.h"
#include "Sphere.h"
#include <cmath>
#include <iostream>
#include <vector>

#define WIDTH  640
#define HEIGHT 640
#define N 8

Matrix projectionMatrix = MatrixFactory::createPerspectiveProjection(
  M_PI/3, 
  4.0f/4.0f,
  1,
  1000
);

void draw(FrameBuffer & fb, Mesh & m) {
  
  m.projectOnto(projectionMatrix);
  m.homogenize();
  std::vector<Micropolygon> polygons = m.getMicropolygons();
  
  std::vector<Micropolygon>::iterator it;
  for (it = polygons.begin(); it != polygons.end(); ++it) {
    float x = it->get(0).get(0);
    float y = it->get(0).get(1);
    fb.drawMicropolygon(*it);
  }

  
}


int main(int argc, char *argv[]) {
  
  Matrix translationVector(10, 0, 10);
  Matrix scaleVector(1, 1, 2);

  
  FrameBuffer fb(WIDTH, HEIGHT);
  
  for (int i=0; i<1; i++) {
    
    Sphere s1(1);
    s1.setColor(0, 255, 0);
    s1.setOpacity(0.7);
    Matrix t1 = MatrixFactory::createIdentity(4);
    t1.scale(10, 10, 10);
    t1.translate(0, 0, 100);
    s1.transform(t1);

    Sphere s2(1);
    s2.setColor(255, 0, 0);
    s2.setOpacity(0.7);
    Matrix t2 = MatrixFactory::createIdentity(4);
    t2.scale(1,1,1);
    t2.translate(1,1, 20);
    s2.transform(t2);
    
    draw(fb, s1);
    draw(fb, s2);
    
    //fb.draw(&s);
    fb.flush(i);
  }

  return 0;
}
