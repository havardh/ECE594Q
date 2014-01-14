#ifndef _MATRIX_H_
#define _MATRIX_H_

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
  ~Matrix(void);

  Matrix & operator=(const Matrix &);
  const Matrix operator*(const Matrix &) const;

  void set(int,int,float);
  void setAll(const float[]);
  float get(int,int) const;

  int getM() const { return _m; }
  int getN() const { return _n; }

  void homogenize(void);
  Matrix & rotate(Axis, float);
  void scale(const Matrix &);
  Matrix & translate(const Matrix &);

};

#endif /* _MATRIX_H_ */
