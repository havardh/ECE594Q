#include "RTPlane.h"

bool RTPlane::isToLeftOf(Ray ray, int axis) {

  if (axis == 0) {
    float Zp = getTriangle(0).getP0().get(2);
    float Zo = ray.getOrigin().get(2);
    float Zd = ray.getDirection().get(2);
    float Xo = ray.getOrigin().get(0);
    float Xd = ray.getDirection().get(0);

    float t = (Zp - Zo) / Zd;
    float x = Xo + Xd*t;

    return x < getTriangle(0).getP0().get(0);

  } else if (axis == 1) {

    float Zp = getTriangle(0).getP0().get(2);
    float Zo = ray.getOrigin().get(2);
    float Zd = ray.getDirection().get(2);
    float Yo = ray.getOrigin().get(1);
    float Yd = ray.getDirection().get(1);

    float t = (Zp - Zo) / Zd;
    float y = Yo + Yd*t;

    return y < getTriangle(0).getP0().get(1);

  } else if (axis == 2) {

    float Xp = getTriangle(0).getP0().get(0);
    float Xo = ray.getOrigin().get(0);
    float Xd = ray.getDirection().get(0);
    float Zo = ray.getOrigin().get(2);
    float Zd = ray.getDirection().get(2);

    float t = (Xp - Xo) / Xd;
    float z = Zo + Zd*t;

    return z < getTriangle(0).getP0().get(2);

  }


  return false;
}
