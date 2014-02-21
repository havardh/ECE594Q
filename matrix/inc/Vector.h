#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <memory>
#include <cmath>
#include <xmmintrin.h>
#include <pmmintrin.h>

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

class Vector {

public:
  Vector() {}
  Vector(float [3]);
  Vector(float,float,float);

  float get(int i) const { return _values[i]; }
  void set(int i, float v) { _values[i] = v; }

  float x() const;
  float y() const;
  float z() const;

  void x(float);
  void y(float);
  void z(float);

  Vector operator-() const;
  const Vector& operator-=(const Vector&);
  Vector operator-(const Vector&) const;

  const Vector& operator+=(const Vector&);
  Vector operator+(const Vector&) const;

  const Vector& operator*=(float);
  friend Vector operator*(float, const Vector&);
  Vector operator*(float) const;

  bool operator==(const Vector&) const;

  float length() const;
  float dot(const Vector&) const;
  float dotSIMD(const Vector&) const;
  const Vector& normalize();
  Vector cross(const Vector&) const;

  void printPoint() const { print(); }
  void print() const { printf("%f %f %f\n", x(), y(), z()); }

private:
  float _values[4];
};

Vector operator*(float, const Vector&);

typedef std::shared_ptr<Vector> VectorPtr;

#endif /* _VECTOR_H_ */
