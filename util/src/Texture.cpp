#include "Texture.h"
#include <assert.h>
#include "CImg.h"
#include "Dbg.h"

using namespace cimg_library;


Texture::Texture(const char * filename) {
  
  CImg<unsigned char> image(filename);
  height = image.height();
  width = image.width();

  for (int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      RTColor c = {
        image(width-j-1,i,0,0) / 255.0,
        image(width-j-1,i,0,1) / 255.0,
        image(width-j-1,i,0,2) / 255.0
      };

      pixels.push_back(c);
    }
  }
}

Texture::~Texture() {}

RTColor Texture::get(float u, float v) {


  assert( u >= 0 && u <= 1);
  assert( v >= 0 && v <= 1);

  int i = (int)((u) * (height-1));
  int j = (int)((v) * (width-1));
  
  assert(i < height);
  assert(j < width);
  assert((i * width + j) < pixels.size());

  return pixels[i*width+j];
}
