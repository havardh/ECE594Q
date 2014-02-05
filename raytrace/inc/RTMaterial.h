#ifndef _RTMATERIAL_H_
#define _RTMATERIAL_H_

#include "RTColor.h"

class RTMaterial {

public:
  RTMaterial() {}
  
  void setDiffColor(RTColor c)   { this->diffColor = c; }
  RTColor getDiffColor()            { return this->diffColor; }
  void setAmbColor(RTColor c)    { this->ambColor = c; }
  RTColor getAmbColor()             { return this->ambColor; }
  void setSpecColor(RTColor c)   { this->specColor = c; }
  RTColor getSpecColor()            { return this->specColor; }
  void setEmissColor(RTColor c)  { this->emsissColor = c; }
  RTColor getEmissColor()           { return this->emsissColor; }
  void setShininess(float s)     { this->shininess = s; }
  float getShininess()            { return this->shininess; }
  void setKTransparency(float t) { this->ktran = t; }
  float getKTransparency()        { return this->ktran; }

private:
  float ktran;
  float shininess;
  RTColor emsissColor;
  RTColor specColor;
  RTColor ambColor;
  RTColor diffColor;

};

#endif /* _RTMATERIAL_H_ */
