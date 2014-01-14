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

  Matrix s(n,n);
  
  for (int i=0; i<n; i++) {
    s.set(i,i, v.get(i,0));
  }

  return s;
  

}
