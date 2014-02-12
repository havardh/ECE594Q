#include "RTMaterial.h"

bool RTMaterial::operator==(const RTMaterial &rhs)  {
  return (fabs(ktran - rhs.ktran) < 0.00001) 
    && (fabs(shininess - rhs.shininess) < 0.00001)
    && diffColor == rhs.diffColor
    && ambColor == rhs.ambColor
    && emissColor == rhs.emissColor
    && specColor == rhs.specColor;
}

bool RTMaterial::operator!=(const RTMaterial &rhs) {
  return ! (*this == rhs);
}

const RTMaterial& RTMaterial::operator+=(const RTMaterial &rhs) {
  
  //rhs.diffColor.print();

  this->ktran += rhs.ktran;
  this->shininess += rhs.shininess;
  this->diffColor += rhs.diffColor;
  this->ambColor += rhs.ambColor;
  this->emissColor += rhs.emissColor;
  this->specColor += rhs.specColor;
  
  return *this;

}

const RTMaterial RTMaterial::operator+(const RTMaterial &rhs) const {
  return RTMaterial(*this) += rhs;
}


const RTMaterial& RTMaterial::operator*=(float rhs) {

  this->ktran *= rhs;
  this->shininess *= rhs;
  this->diffColor *= rhs;
  this->ambColor *= rhs;
  this->emissColor *= rhs;
  this->specColor *= rhs;


  //this->diffColor.print();
  
  return *this;  

}

const RTMaterial RTMaterial::operator*(float rhs) const {
  RTMaterial m = *this;
  m *= rhs;
  return m;
}
