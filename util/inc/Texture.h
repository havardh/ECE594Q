#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Color.h"
#include <vector>

class Texture {

private:
  int width, height;
  std::vector<Color> pixels;

public:
  Texture() {}
  Texture(const char*);

  ~Texture();

  Color get(float, float);

};

#endif /* _TEXTURE_H_ */
