#ifndef _COLORSHADERTEXTURE_H_
#define _COLORSHADERTEXTURE_H_

#include "ColorShader.h"
#include "Texture.h"

class ColorShaderTexture : public ColorShader {

public:
  ColorShaderTexture(const char* filename) :
    texture(filename) {}

  virtual RTMaterial shade(float u, float v, RTMaterial m);

private: 
  Texture texture;

};

#endif /* _COLORSHADERTEXTURE_H_ */
