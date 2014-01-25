#ifndef _RSRANDOMSHADER_H_
#define _RSRANDOMSHADER_H_

#include <cmath>
#include "Shader.h"


int (*randfn) (void) = &rand;

void setRsRandomShaderRandFunction( int (*rand)(void) ) {
  randfn = rand;
}

void RsRandomShader(ShaderParam s) {
  Color r = { 
    (uint8_t)(randfn()%256),
    (uint8_t)(randfn()%256),
    (uint8_t)(randfn()%256)
  };
  s.meshPoint->color = r;
}

#endif /* _RSRANDOMSHADER_H_ */
