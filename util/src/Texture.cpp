#include "Texture.h"

#include "CImg.h"

using namespace cimg_library;


Texture::Texture(const char * filename) {
  
  CImg<unsigned char> image(filename);
  width = image.width();
  height = image.height();

  for (int i=0; i<width; i++) {
    for (int j=0; j<height; j++) {
      RTColor c = {
        image(i,j,0,0) / 255.0,
        image(i,j,0,1) / 255.0,
        image(i,j,0,2) / 255.0
      };

      pixels.push_back(c);
    }
  }

}

Texture::~Texture() {

}

RTColor Texture::get(float u, float v) {

  int i = (int)(u * (height-1));
  int j = (int)(v * (width-1));

  return pixels[(size_t)(i*width+j)];
}
