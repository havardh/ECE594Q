#ifndef _RSTEXTURESHADER_H_
#define _RSTEXTURESHADER_H_

#include "Texture.h"
#include "Shader.h"

static Texture texture("textures/earth.jpg");

void RsTextureShader(ShaderParam s) {

  s.meshPoint->color = texture.get(s.u, s.v);

}

#endif /* _RSTEXTURESHADER_H_ */
