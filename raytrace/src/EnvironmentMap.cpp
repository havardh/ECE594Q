#include "EnvironmentMap.h"
#include "CImg.h"
#include <stdlib.h>

EnvironmentMap::EnvironmentMap(const char *filename) 
  : _texture(filename) {
}

RTColor EnvironmentMap::get(Ray ray) {

  float u,v;
  setUV(ray, u,v);

  if (u == 0 && v == 0) {
    return RTColor(1,0,0);
  }

  boxUV(u,v);

  return _texture.get(u,v);
}

Section EnvironmentMap::section(Vector direction) {

  float xabs = fabs(direction.x());
  float yabs = fabs(direction.y());
  float zabs = fabs(direction.z());

  if ( xabs > yabs && xabs > zabs ) {
    if (direction.x() > 0) {
      return Xp;
    } else {
      return Xn;
    }
  } else if ( yabs > zabs ) {
    if (direction.y() > 0) {
      return Yp;
    } else {
      return Yn;
    }
  } else {
    if (direction.z() > 0) {
      return Zp;
    } else {
      return Zn;
    }
  }
}

void EnvironmentMap::setUV(Ray ray, float &u, float &v) {

  Vector d = ray.getDirection();
  Section s = section(d);

  float du = (0.25/2);
  float dv = ((1/3.0)/2);

  u = v = 0;


  switch (s) {

  case Xp: {
    u = (3/8.0) - (d.y() / d.x()) * du;
    v = (5/6.0) + (d.z() / d.x()) * dv;
    break;
  }

  case Xn: {
    u = (3/8.0) + (d.y() / d.x()) * du;
    v = (1/6.0) + (d.z() / d.x()) * dv;
    break;
  }

  case Zp: {
    u = 0.375 - (d.y() / d.z()) * du;
    v = 0.5   + (d.x() / d.z()) * dv;
    break;
  }
  case Zn: {
    u = 0.875 - (d.y() / d.z()) * du;
    v = 0.5   + (d.x() / d.z()) * dv;
    break;
  }

  case Yp: {
    u = (1/8.0) - (d.z() / d.y()) * du;
    v = 0.5     + (d.x() / d.y()) * dv;
    break;
  }

  case Yn: {
    u = (5/8.0) - (d.z() / d.y()) * du;
    v = 0.5     - (d.x() / d.y()) * dv;
    break;
  }


  }

  //assert( u >= 0 && u <= 1);
  //assert( v >= 0 && v <= 1);

}

void EnvironmentMap::boxUV(float &u,float &v) {

  if (u < 0.250001 || u > 0.499999) {
    
    if (v < 0.333) {
      v = 0.333;
    }

    if (v > 0.666) {
      v = 0.666;
    }

  }

}
