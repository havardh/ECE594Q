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
