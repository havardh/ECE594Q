#include "Matrix.h"

#define IX(row, col) ((row) * this->_n + (col))

Matrix::Matrix() : _m(0), _n(0), matrix(0) {}

Matrix::Matrix(const Matrix &other) : _m(other._m), _n(other._n) {

  if ( _m > 0 && _n > 0 ) {
    this->allocate();
    
    for (int i=0; i<_m*_n; i++) {
      this->matrix[i] = other.matrix[i];
    }
  }

}

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

Matrix::Matrix(float x, float y, float z) : _m(3), _n(1) {

  this->allocate();

  this->matrix[0] = x;
  this->matrix[1] = y;
  this->matrix[2] = z;
  
}

Matrix::Matrix(float x, float y, float z, float w) : _m(4), _n(1) {

  this->allocate();

  this->matrix[0] = x;
  this->matrix[1] = y;
  this->matrix[2] = z;
  this->matrix[3] = w;
  
}

void Matrix::allocate(void) {
  this->matrix = new float[this->_m*this->_n];
}

Matrix::~Matrix(void) {
  delete [] this->matrix;
}

Matrix & Matrix::operator=(const Matrix &rhs) {


  if ( this->_m != rhs._m || this->_n != rhs._n) {
    delete[] this->matrix;
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

void Matrix::set(int i, float f) {
  this->set(i,0,f);
}

void Matrix::setAll(const float values[]) {

  for (int i=0; i<this->_m*this->_n; i++) {
    this->matrix[i] = values[i];
  }
  
}

float Matrix::get(int row, int col) const {

  return this->matrix[ IX(row, col) ];

}

float Matrix::get(int i) const {
  return this->get(i,0);
}

Matrix & Matrix::homogenize(void) {

  int m = this->_m, n = this->_n;

  float factor = this->matrix[ IX(m-1,n-1) ];

  for (int i=0; i<m; i++) {
    for (int j = 0; j < n; j++) {
      this->matrix[ IX(i,j)] /= factor;
    }
  }

  return *this;

}

Matrix & Matrix::scale(const Matrix &v) {
  
  Matrix scaleMatrix = MatrixFactory::createScale(v);

  // *this *= scaleMatrix;
  (*this) = scaleMatrix * (*this);

  return *this;

}

Matrix & Matrix::scale(float x, float y, float z) {
  Matrix v(3,1);
  float values[] = { x, y, z };
  v.setAll(values);

  return this->scale(v);
}

Matrix & Matrix::translate(const Matrix &v) {

  Matrix translationMatrix = MatrixFactory::createTranslation(v);

  (*this) = translationMatrix * (*this);

  return *this;

}

Matrix & Matrix::translate(float x, float y, float z) {
  Matrix v(3,1);
  float values[] = { x, y, z };
  v.setAll(values);

  return this->translate(v);
}

Matrix & Matrix::rotate(Axis axis, float angle) {
  
  Matrix rotationMatrix = MatrixFactory::createRotation(axis, angle);

  (*this) = rotationMatrix * (*this);

  return *this;

   
}

Matrix & Matrix::projectOnto(const Matrix &space) {
  
  (*this) = space * (*this);

  return *this;

}


float Matrix::dot(const Matrix &other) const {

  float result = 0.0;

  for (int i=0; i<this->_m; i++) {
    result += this->get(i,0) * other.get(i,0);
  }

  return result;

}
