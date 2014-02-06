#ifndef _RTCOLOR_H_
#define _RTCOLOR_H_

#include <stdint.h>

class RTColor {

public:

  RTColor(uint8_t r, uint8_t g, uint8_t b) {
    this->setColor(r,g,b);
  }
  RTColor(float r, float g, float b) {
    this->setColor(r,g,b);
  }
  RTColor(float spec[3]) {
    this->setColor(spec[0], spec[1], spec[2]);
  }
  RTColor() {
    float z = 0;
    this->setColor(z,z,z);
  }

  void setColor(uint8_t r, uint8_t g, uint8_t b) {
    this->_red   = (float)(r/255.0);
    this->_green = (float)(g/255.0);
    this->_blue  = (float)(b/255.0);
  }

  void setColor(float r, float g, float b) {
    this->_red = r; 
    this->_green = g; 
    this->_blue = b;
  }

  static const RTColor BLACK;
  static const RTColor GRAY;
  static const RTColor WHITE;

  uint8_t getRGBRed() const { return (uint8_t)(_red*255); }
  float getRed() const { return _red; }
  uint8_t getRGBGreen() const { return (uint8_t)(_green*255); }
  float getGreen() const { return _green; }
  uint8_t getRGBBlue() const { return (uint8_t)(_blue*255); }
  float getBlue() const { return _blue; }

private:
  float _red, _green, _blue;

};

#endif /* _RTCOLOR_H_ */
