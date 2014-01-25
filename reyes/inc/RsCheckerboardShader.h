#ifndef _RSCHECKERBOARDSHADER_H_
#define _RSCHECKERBOARDSHADER_H_

#include "Shader.h"

void RsCheckerboardShader(ShaderParam s) {

  int i = (int)(s.u * 10);
  int j = (int)(s.v * 10);

  Color light = {200, 200, 200};
  Color dark = { 50, 50, 50 };

  if (i % 2 == 0) {
    if (j % 2 == 0) {
      s.meshPoint->color = light;
    } else {
      s.meshPoint->color = dark;
    }
  } else {
    if (j % 2 == 0) {
      s.meshPoint->color = dark;
    } else {
      s.meshPoint->color = light;
    }
  } 

}

#endif /* _RSCHECKERBOARDSHADER_H_ */
