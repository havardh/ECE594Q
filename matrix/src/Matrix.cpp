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

Matrix::Matrix(float vals[3]) : _m(3), _n(1) { 

  this->allocate();
  this->setAll(vals);
}

Matrix::Matrix(float vals[4][4] ) : _m(4), _n(4) {
  
  this->allocate();

  for (int i=0; i<_m; i++) {
    for (int j=0; j<_n; j++) {
      set(i,j, vals[i][j]);
    }
  }

}

void Matrix::allocate(void) {
  this->matrix = new float[this->_m*this->_n];
}

Matrix::~Matrix(void) {
  if (this->matrix) {
    delete [] this->matrix;
  }
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

bool Matrix::operator==(const Matrix &rhs) const {
  
  if (_m != rhs._m || _n != rhs._n) 
    return false;

  for(int i=0; i<_m; i++) 
    for (int j=0; j<_n; j++) 
      if (get(i,j) != rhs.get(i,j))
        return false;
  
  return true;
}

bool Matrix::operator!=(const Matrix &rhs) const {
  
  return !(*this == rhs);

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

const Matrix Matrix::operator/(const Matrix &rhs) const {
  
  int m = this->_m;
  int n = this->_n;

  Matrix result(m,n);
  
  for (int i=0; i<m; i++) {
    for(int j=0; j<n; j++) {
      result.set(i,j, this->get(i,j) / rhs.get(i,j));
    }
  }
  return result;
}

const Matrix Matrix::operator*(const int &c) const {
  return *this * (double)c;
}

const Matrix Matrix::operator*(const float &c) const {
  return *this * (double)c;
}

const Matrix operator*(const double &lhs, const Matrix &rhs) {
  return rhs * lhs;
}

const Vector Matrix::operator*(const Vector &v) const {

  Vector r;

  r.set(0, (v.get(0) * get(0,0) + v.get(1) * get(0,1) + v.get(2) * get(0,2) + v.get(3) * get(0,3)));
  r.set(1, (v.get(0) * get(1,0) + v.get(1) * get(1,1) + v.get(2) * get(1,2) + v.get(3) * get(1,3)));
  r.set(2, (v.get(0) * get(2,0) + v.get(1) * get(2,1) + v.get(2) * get(2,2) + v.get(3) * get(2,3)));
  r.set(3, (v.get(0) * get(3,0) + v.get(1) * get(3,1) + v.get(2) * get(3,2) + v.get(3) * get(3,3)));
  
  r.x(r.x() / r.get(3));
  r.y(r.y() / r.get(3));
  r.z(r.z() / r.get(3));
  r.set(3,1);

  return r;

}

const Matrix Matrix::operator*(const double &c) const {
  
  int m = this->_m;
  int n = this->_n;

  float fc = (float)c;

  Matrix result(m, n);

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      result.set(i, j, this->get(i, j)*fc);
    }
  }
  return result;
}

const Matrix Matrix::operator+(const Matrix &rhs) const {
  int m = this->_m;
  int n = this->_n;

  Matrix result(m, n);

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      result.set(i, j, this->get(i, j) + rhs.get(i,j));
    }
  }
  return result;
}

const Matrix Matrix::operator-(const Matrix &rhs) const {
  
  int m = this->_m; 
  int n = this->_n; 
  
  Matrix result(m,n);

  for (int i=0; i<m; i++) {
    for (int j=0; j<n; j++) {
      result.set(i,j, this->get(i,j) - rhs.get(i,j));
    }
  }

  return result;
}

const Matrix Matrix::operator-() const {

  Matrix result(this->_m, this->_n);

  for (int i=0; i<_m; i++) {
    for (int j=0; j<_n; j++) {
      result.set(i,j, -this->get(i,j));
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

float Matrix::length(void) const {
  
  float sum=0;

  for (int i=0; i<_m; i++) {
    float v = this->get(i);
    sum += v*v;
  }

  return (float)sqrt(sum);
}

Matrix& Matrix::normalize(void) {

  float L = this->length();


  if (L != 0) {
    for (int i=0; i<_m; i++) {
      this->set(i, this->get(i) / L);
    }
  }
  
  return *this;

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

Matrix & Matrix::transform(const Matrix &v) {

  (*this) = v * (*this);

  return *this;

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

Matrix Matrix::hadamardProduct(const Matrix &other) const {

  Matrix result(_m, _n);

  for (int i=0; i<_m; i++) {
    for (int j=0; j<_n; j++) {
      result.set(i, j, get(i,j) * other.get(i,j));
    }
  }

  return result;
}

Matrix Matrix::crossProduct(const Matrix &other) const {
  
  float u1 = get(0);
  float u2 = get(1);
  float u3 = get(2);
  float v1 = other.get(0);
  float v2 = other.get(1);
  float v3 = other.get(2);
  
  return Matrix(
    u2*v3-u3*v2,
    -(u1*v3-u3*v1),
    u1*v2-u2*v1
  );
  
}

Matrix Matrix::abs() const {

  Matrix result = *this;
  
  for(int i=0; i<_m*_n; i++) {
    result.set(i, (float)fabs(result.get(i)));
  }

  return result;
}
