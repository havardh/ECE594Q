#ifndef _RTMATERIAL_H_
#define _RTMATERIAL_H_

#include "RTColor.h"

class RTMaterial {

public:
  RTMaterial() : 
    ktran(0), 
    shininess(0),
    emissColor(0,0,0),
    ambColor(0,0,0),
    diffColor(0,0,0) {}
  
  void setDiffColor(RTColor c) { this->diffColor = c; }
  RTColor getDiffColor() const { return this->diffColor; }
  void setAmbColor(RTColor c) { this->ambColor = c; }
  RTColor getAmbColor() const { return this->ambColor; }
  void setSpecColor(RTColor c) { this->specColor = c; }
  RTColor getSpecColor() const { return this->specColor; }
  void setEmissColor(RTColor c) { this->emissColor = c; }
  RTColor getEmissColor() const { return this->emissColor; }
  void setShininess(float s) { this->shininess = s; }
  float getShininess() const { return this->shininess; }
  void setKTransparency(float t) { this->ktran = t; }
  float getKTransparency() const { return this->ktran; }

  bool operator==(const RTMaterial &);
  bool operator!=(const RTMaterial &);
  const RTMaterial& operator+=(const RTMaterial&);
  const RTMaterial operator+(const RTMaterial&) const;
  const RTMaterial& operator*=(float);
  const RTMaterial operator*(float) const;

private:
  float ktran;
  float shininess;
  RTColor emissColor;
  RTColor specColor;
  RTColor ambColor;
  RTColor diffColor;

};

#endif /* _RTMATERIAL_H_ */
