#include "Matrix.h"

#define IX(row, col) ((row) * this->_n + (col))

Matrix::Matrix() : _m(0), _n(0), matrix(0) {}

Matrix::Matrix(int n) : _m(n), _n(n) {

  if (n > 0) {
    this->allocate();

    for (int i=0; i<this->_m*this->_n; i++) {
      this->matrix[i] = 0;
    }
  }

}

Matrix::Matrix(int m, int n) : _m(m), _n(n) {

  if ( m > 0 && n > 0) {
    this->allocate();

    for (int i=0; i<this->_m*this->_n; i++) {
      this->matrix[i] = 0;
    }
  }

}

void Matrix::allocate(void) {
  this->matrix = (float*) malloc(sizeof(float) * (unsigned long)(this->_m * this->_n));
}

Matrix::~Matrix(void) {

  free (this->matrix);

}

Matrix & Matrix::operator=(const Matrix &rhs) {

  if ( this->_m != rhs._m || this->_n != rhs._n) {
    free(this->matrix);
    this->_m = rhs._m;
    this->_n = rhs._n;
    this->allocate();
  }

  for (int i=0; i<_m*_n; i++) {
    this->matrix[i] = rhs.matrix[i];
  }

  return *this;

}

const Matrix Matrix::operator*(const Matrix &rhs) const {
  
  int m = this->_m;
  int n = rhs._n;

  Matrix result(m, n);

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      float value = 0;
      for (int k=0; k<this->_n; k++) {
        value += this->get(i, k) * rhs.get(k, j);
      }
      result.set(i, j, value);
    }
  }
  return result;
}

void Matrix::set(int row, int col, float f) {

  this->matrix[ IX(row, col) ] = f;

}

void Matrix::setAll(const float values[]) {

  for (int i=0; i<this->_m*this->_n; i++) {
    this->matrix[i] = values[i];
  }
  
}

float Matrix::get(int row, int col) const {

  return this->matrix[ IX(row, col) ];

}

void Matrix::homogenize(void) {

  int m = this->_m, n = this->_n;

  float factor = this->matrix[ IX(m-1,n-1) ];

  for (int i=0; i<m; i++) {
    for (int j = 0; j < n; j++) {
      this->matrix[ IX(i,j)] /= factor;
    }
  }

}

void Matrix::scale(const Matrix &v) {
  
  Matrix scaleMatrix = MatrixFactory::createScale(v);

  // *this *= scaleMatrix;
  (*this) = scaleMatrix * (*this);

}

Matrix & Matrix::translate(const Matrix &v) {

  Matrix translationMatrix = MatrixFactory::createTranslation(v);

  (*this) = translationMatrix * (*this);

  return *this;

}

Matrix & Matrix::rotate(Axis axis, float angle) {
  
  Matrix rotationMatrix = MatrixFactory::createRotation(axis, angle);

  (*this) = rotationMatrix * (*this);

  return *this;

   
}
