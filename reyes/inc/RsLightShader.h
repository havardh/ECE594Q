#ifndef _RSLIGHTSHADER_H_
#define _RSLIGHTSHADER_H_

#include "Shader.h"
#include "Matrix.h"

Matrix L;

void RsLightShader(ShaderParam s) {

  Color c = s->meshPoint.color;
  
  float fac = s->meshPoint->normal.crossProduct(L);
  c.red *= fac;
  c.green *= fac;
  c.blue *= fac;

  s->meshPoint.color = c;
   

}

#endif /* _RSLIGHTSHADER_H_ */
