#include "Vector.h"

Vector::Vector(float values[3]) {

  memcpy(_values, values, sizeof(float)*3);

}

Vector::Vector(float x, float y, float z) {

  _values[0] = x;
  _values[1] = y;
  _values[2] = z;
  
}

float Vector::x() const { return _values[0]; }
float Vector::y() const { return _values[1]; }
float Vector::z() const { return _values[2]; }

void Vector::x(float v) { _values[0] = v; }
void Vector::y(float v) { _values[1] = v; }
void Vector::z(float v) { _values[2] = v; }

Vector Vector::operator-() const {

  return Vector(-x(), -y(), -z());

}

const Vector& Vector::operator-=(const Vector &rhs) {

  x(x() - rhs.x());
  y(y() - rhs.y());
  z(z() - rhs.z());

  return *this;

}

Vector Vector::operator-(const Vector &rhs) const {

  return Vector(*this) -= rhs;

}

const Vector& Vector::operator+=(const Vector &rhs) {

  x(x() + rhs.x());
  y(y() + rhs.y());
  z(z() + rhs.z());

  return *this;

}

Vector Vector::operator+(const Vector &rhs) const {
  
  return Vector(*this) += rhs;

}

bool Vector::operator==(const Vector &other) const {

  Vector v(*this - other);

  return fabs(v.x()) < 0.0001 && fabs(v.y()) < 0.0001 && fabs(v.z()) < 0.0001;
  

}

float Vector::length() const {
  return (float)sqrt(x()*x() + y()*y() + z()*z());
}

float Vector::dot(const Vector &o) const {
  return x() * o.x() + y() * o.y() + z() * o.z();
}

const Vector& Vector::normalize() {
  float l = this->length();

  x(x()/l);
  y(y()/l);
  z(z()/l);

  return *this;
}

const Vector& Vector::operator*=(float rhs)  {

  x(x()*rhs);
  y(y()*rhs);
  z(z()*rhs);

  return *this;
}

Vector Vector::operator*(float rhs) const {
  return Vector(*this) *= rhs;
}

Vector operator*(float lhs, const Vector &rhs) {
  return Vector(rhs) *= lhs;
}

Vector Vector::cross(const Vector &o) const {
  return Vector(
    y() * o.z() - z() * o.y(),
    -(x() * o.z() - z() * o.x()),
    x() * o.y() - y() * o.x()
  );
}
