#include "MatrixFactory.h"

Matrix MatrixFactory::createIdentity(int n) {

  Matrix m(n,n);

  for (int i=0; i<n; i++) {
    m.set(i,i,1.0);
  }
  return m;
  
}

Matrix MatrixFactory::createTranslation(const Matrix &v) {

  int n = v.getM();

  Matrix m = MatrixFactory::createIdentity(n+1);

  for (int i=0; i<n; i++) {
    m.set(i, n, v.get(i,0));
  }

  return m;

}

Matrix MatrixFactory::createScale(const Matrix &v) {

  int n = v.getM();

  Matrix s(n+1,n+1);
  
  for (int i=0; i<n; i++) {
    s.set(i,i, v.get(i,0));
  }
  s.set(n,n, 1.0);

  return s;
  

}

Matrix MatrixFactory::createRotation(Axis axis, float angle) {
  
  Matrix m = MatrixFactory::createIdentity(4);

  switch (axis) {
  case X: 
    m.set(1,1, (float)cos(angle));
    m.set(1,2, (float)-sin(angle));
    m.set(2,2, (float)cos(angle));
    m.set(2,1, (float)sin(angle));    
    break;
  case Y: 
    m.set(0,0, (float)cos(angle));
    m.set(0,2, (float)-sin(angle));
    m.set(2,2, (float)cos(angle));
    m.set(2,0, (float)sin(angle));
    break;
  case Z: 
    m.set(0,0, (float)cos(angle));
    m.set(0,1, (float)-sin(angle));
    m.set(1,1, (float)cos(angle));
    m.set(1,0, (float)sin(angle));
    break;
  }
  
  return m;

}

Matrix MatrixFactory::createPerspectiveProjection(float theta, float r, float hither, float yon) {

  Matrix m(4,4);

  m.set(0,0, (float)(1.0/tan(theta/2)));
  m.set(1,1, (float)(1.0/tan(theta/(r*2))));
  m.set(2,2, yon/(yon-hither));
  m.set(2,3, (-yon*hither)/(yon-hither));
  m.set(3,2, 1.0);

  return m;

}

Matrix MatrixFactory::createOrthogonalProjection(float left, float right, float top, float bottom, float near, float far) {
  (void) left;
  (void) right;
  (void) top;
  (void) bottom;
  (void) near;
  (void) far;

  Matrix m(4,4);
  
  m.set(0,0, 2.0f/(right-left));
  m.set(1,1, 2.0f/(top-bottom));
  m.set(2,2, 2.0f/(far-near));

  m.set(0,3, -(right+left)/2.0f);
  m.set(1,3, -(top+bottom)/2.0f);
  m.set(2,3, -(far+near)/2.0f);
  m.set(3,3, 1.0);

  return m;

}
