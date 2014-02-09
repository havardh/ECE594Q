#include "RTColor.h"

static float b=0;
static float g=0.5;
static float w=1;


const RTColor RTColor::BLACK = RTColor(b,b,b);
const RTColor RTColor::GRAY  = RTColor(g,g,g);
const RTColor RTColor::WHITE = RTColor(w,w,w);

bool RTColor::operator<(float rhs) const {

  return _red < rhs && _green < rhs && _blue < rhs;

}

bool RTColor::operator==(const RTColor &rhs) const {
  return fabs(_red - rhs._red) < 0.000001
                                 && fabs(_green - rhs._green) < 0.000001
                                                                && fabs(_blue - rhs._blue) < 0.000001;
}

bool RTColor::operator!=(const RTColor &rhs) const {
  return ! (*this == rhs);
}

const RTColor RTColor::operator*(float factor) const {
  return RTColor(_red*factor, _green*factor, _blue*factor);
}

const RTColor RTColor::operator*(const RTColor & rhs) const {
  return RTColor(_red*rhs._red, _green*rhs._green, _blue*rhs._blue);
}

const RTColor& RTColor::operator+=(const RTColor &rhs) {
  setColor(
    this->_red + rhs._red,
    this->_green + rhs._green,
    this->_blue + rhs._blue
  );
  return *this;
}

const RTColor RTColor::operator+(const RTColor & rhs) const {
  RTColor c(*this);
  return c += rhs;
}

const RTColor RTColor::operator+(float rhs) const {
  return RTColor(_red+rhs,_green+rhs,_blue+rhs);
}
