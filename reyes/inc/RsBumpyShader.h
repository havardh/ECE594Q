#ifndef _RSBUMPYSHADER_H_
#define _RSBUMPYSHADER_H_

#include "Shader.h"
#include <cmath>

void RsBumpyShader(ShaderParam s) {

  // Should have had surface normal to dislocate by

  int randomNumber = rand();
  float normalized = (randomNumber % 100) / 100.0;

  Matrix *p = &s.meshPoint->point;
  float x = p->get(0);
  float y = p->get(1);
  float z = p->get(2);

  p->set(0, x + normalized);
  p->set(1, y + normalized);
  p->set(2, z + normalized);

}

#endif /* _RSBUMPYSHADER_H_ */
