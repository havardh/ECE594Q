#include "Texture.h"

#include "CImg.h"

using namespace cimg_library;


Texture::Texture(const char * filename) {
  
  CImg<unsigned char> image(filename);
  width = image.width();
  height = image.height();

  for (int i=0; i<width; i++) {
    for (int j=0; j<height; j++) {
      Color c = {
        image(i,j,0,0), 
        image(i,j,0,1), 
        image(i,j,0,2) 
      };
      pixels.push_back(c);
    }
  }

}

Texture::~Texture() {

}

Color Texture::get(float u, float v) {
  int i = (int)(u * (width-1));
  int j = (int)(v * (height-1));

  return pixels[(size_t)(i*width+j)];
}
