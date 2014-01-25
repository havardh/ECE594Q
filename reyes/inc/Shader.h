#ifndef _SHADER_H_
#define _SHADER_H_

#include "Mesh.h"

typedef struct {

  float u,v;
  MeshPoint *meshPoint;

} ShaderParam;

typedef void (*ShaderFunction)(ShaderParam);

#endif /* _SHADER_H_ */
