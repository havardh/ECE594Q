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

  (void) axis;

  int d = axis == Z ? 0 : 1;

  m.set(d+0,d+0, (float)cos(angle));
  m.set(d+0,d+1, (float)-sin(angle));
  m.set(d+1,d+1, (float)cos(angle));
  m.set(d+1,d+0, (float)sin(angle));

  return m;

}
