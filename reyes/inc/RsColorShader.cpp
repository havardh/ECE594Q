#ifndef _RANDOMSHADER_H_
#define _RANDOMSHADER_H_

#include "Shader.h"

void RsRandomShader(ShaderParam s) {
  Color r = {1,1,1};
  s.meshPoint->color = r;
}

#endif /* _RANDOMSHADER_H_ */
