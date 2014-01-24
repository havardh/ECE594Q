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

void draw(FrameBuffer & fb, Shape & shape) {
  
  shape.projectOnto(projectionMatrix);
  shape.homogenize();
  std::vector<Micropolygon> polygons = shape.getMicropolygons();
  
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
    
    {
      Sphere s(1);
      s.setColor(0, 255, 0);
      s.setOpacity(0.7);
      Matrix t = MatrixFactory::createIdentity(4);
      t.scale(10, 10, 10);
      t.translate(0, 0, 100);
      s.transform(t);
      draw(fb, s);
    }

    {
      Sphere s(1);
      s.setColor(0, 0, 255);
      s.setOpacity(0.7);
      Matrix t = MatrixFactory::createIdentity(4);
      t.scale(1.7,1.7,1.7);
      t.translate(5,5, 60);
      s.transform(t);
      draw(fb, s);
    }    

    {
      Sphere s(1);
      s.setColor(255, 0, 0);
      s.setOpacity(0.3);
      Matrix t = MatrixFactory::createIdentity(4);
      t.scale(1,1,1);
      t.translate(1,1, 20);
      s.transform(t);
      draw(fb, s);
    }    
    //fb.draw(&s);
    fb.flush(i);
  }

  return 0;
}
