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

Matrix & vector3(float x, float y, float z) {
  Matrix *m = new Matrix(3,1);
  float v[] = { x, y, z };
  m->setAll(v);
  return *m;
}

Matrix & vector4(float x, float y, float z) {
  Matrix *m = new Matrix(4,1);
  float v[] = { x, y, z, 1 };
  m->setAll(v);
  return *m;
}

void project(Matrix *V, int n) {

  for (int i=0; i<N; i++) {
    V[i].projectOnto(projectionMatrix);
    V[i].homogenize();
  }
}

int main(int argc, char *argv[]) {
  
  Matrix translationVector = vector3(10, 0, 10);
  Matrix scaleVector = vector3(1, 1, 2);

  Matrix V[N];

  int x0 = 10;
  int y0 = 0;
  int z0 = 100;

  int dx = 10;
  int dy = 10;
  int dz = 10;

  V[0] = vector4(x0,    y0,    z0);
  V[1] = vector4(x0,    y0+dy, z0);
  V[2] = vector4(x0+dx, y0,    z0);
  V[3] = vector4(x0+dx, y0+dy, z0);
  V[4] = vector4(x0,    y0,    z0+dz);
  V[5] = vector4(x0,    y0+dy, z0+dz);
  V[6] = vector4(x0+dx, y0,    z0+dz);
  V[7] = vector4(x0+dx, y0+dy, z0+dz);

  Sphere sphere(1);
  Matrix transformMatrix = MatrixFactory::createIdentity(4);
  transformMatrix.scale(10, 10, 10);
  transformMatrix.translate(0, 0, 100);
  sphere.transform(transformMatrix);
  
  //project(V, N);

  Matrix pts[3];
  pts[0] = vector4(-10, -10, 100);
  pts[1] = vector4(-10, -10, 200);
  pts[2] = vector4(-10, -10, 300);
  
  sphere.projectOnto(projectionMatrix);
  sphere.homogenize();
  std::vector<Micropolygon> polygons = sphere.getMicropolygons();

  FrameBuffer fb(WIDTH, HEIGHT);
  fb.setProjectionMatrix(projectionMatrix);
  //fb.draw(&sphere);
  
  for (std::vector<Micropolygon>::iterator iter = polygons.begin();
       iter != polygons.end();
       ++iter) {
    BoundingBox box = iter->getBoundingBox();
    int x = (int)floor(box.getX() * WIDTH + WIDTH/2);
    int y = (int)floor(box.getY() * HEIGHT + HEIGHT/2);
    int dx = (int)ceil(box.getDX() * WIDTH);
    int dy = (int)ceil(box.getDY() * HEIGHT);
    fb.drawRectangle(x, y, dx, dy);
  }
  
  //fb.draw(pts, 3);
  fb.flush();

  return 0;
}
