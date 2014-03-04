#ifndef _ENVIRONMENTMAP_H_
#define _ENVIRONMENTMAP_H_

#include "RTColor.h"
#include "Ray.h"
#include "Texture.h"
#include "Dbg.h"
#include <vector>
#include <assert.h>


typedef enum {
  Xp, Xn, Yp, Yn, Zp, Zn
} Section;

class EnvironmentMap {

private:
  Texture _texture;
  Section section(Vector);

public:
  EnvironmentMap() : _texture() {}
  EnvironmentMap(const char*);

  RTColor get(Ray);
  void setUV(Ray,float&,float&);
  void boxUV(float&,float&);
  
};

#endif /* _ENVIRONMENTMAP_H_ */
