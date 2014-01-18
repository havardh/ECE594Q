#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include "MatrixFactory.h"
#include "Axis.h"

class Matrix {

 private:
  int _m, _n;
  float *matrix;

  void allocate(void);

 public:
  
  Matrix();
  Matrix(int);
  Matrix(int, int);
  Matrix(const Matrix &);
  ~Matrix(void);

  Matrix & operator=(const Matrix &);
  const Matrix operator*(const Matrix &) const;

  void set(int,int,float);
  void setAll(const float[]);
  float get(int,int) const;

  int getM() const { return _m; }
  int getN() const { return _n; }

  Matrix & homogenize(void);
  Matrix & rotate(Axis, float);
  Matrix & scale(const Matrix &);
  Matrix & translate(const Matrix &);

  Matrix & projectOnto(const Matrix &);

  float dot(const Matrix &) const;

  void printMatrix(void) {
    for (int i=0; i<_m; i++) {
      for (int j=0; j<_n; j++) {
        printf("%2.2f ", get(i,j));
      }
      printf("\n");
    }
  }

  void printPoint(void) { 
    printf("(%8.8f, %8.8f, %8.8f, %8.8f)\n", get(0,0), get(1,0), get(2,0), get(3,0)); 
  }

};

#endif /* _MATRIX_H_ */
