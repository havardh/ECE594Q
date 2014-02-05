#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <stdio.h>
#include "MatrixFactory.h"
#include "Axis.h"
#include <cmath>

class Matrix {

private:
  int _m, _n;
  float *matrix;

  void allocate(void);

public:
  
  Matrix();
  Matrix(int);
  Matrix(int, int);
  Matrix(float, float, float);
  Matrix(float, float, float, float);
  Matrix(float[3]);
  Matrix(float[4][4]);
  Matrix(const Matrix &);
  ~Matrix(void);

  Matrix & operator=(const Matrix &);
  bool operator==(const Matrix &) const;
  bool operator!=(const Matrix &) const;
  const Matrix operator/(const Matrix &) const;
  const Matrix operator*(const Matrix &) const;
  const Matrix operator*(const int &) const;
  const Matrix operator*(const float &) const;
  const Matrix operator*(const double &) const;
  const Matrix operator+(const Matrix &) const;
  const Matrix operator-(const Matrix &) const;

  Matrix crossProduct(const Matrix &) const;
  Matrix abs() const;

  void set(int,int,float);
  void set(int, float);
  void setAll(const float[]);
  float get(int,int) const;
  float get(int) const;

  int getM() const { return _m; }
  int getN() const { return _n; }

  float length(void) const;
  Matrix & normalize(void);
  Matrix & homogenize(void);
  Matrix & rotate(Axis, float);
  Matrix & scale(const Matrix &);
  Matrix & scale(float x, float y, float z);
  Matrix & translate(const Matrix &);
  Matrix & translate(float x, float y, float z);
  Matrix & transform(const Matrix &);

  Matrix & projectOnto(const Matrix &);

  float dot(const Matrix &) const;

  void printMatrix(void) const {
    for (int i=0; i<_m; i++) {
      for (int j=0; j<_n; j++) {
        printf("%2.2f ", get(i,j));
      }
      printf("\n");
    }
  }

  void printPoint(void) const { 
    if (_m == 4)
      printf("(%8.8f, %8.8f, %8.8f, %8.8f)\n", get(0,0), get(1,0), get(2,0), get(3,0)); 
    if (_m == 3)
      printf("%8.8f %8.8f %8.8f\n", get(0,0), get(1,0), get(2,0)); 
  }

};

typedef std::shared_ptr<Matrix> MatrixPtr;
const Matrix operator *(const double &lhs, const Matrix &rhs);

#endif /* _MATRIX_H_ */
