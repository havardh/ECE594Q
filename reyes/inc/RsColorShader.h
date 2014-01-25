#ifndef _RSCOLORSHADER_H_
#define _RSCOLORSHADER_H_

#include "Shader.h"

void RsColorShader(ShaderParam s) {
  Color r = {1,1,1};
  s.meshPoint->color = r;
}

#endif /* _RSCOLORSHADER_H_ */
