#include "RayFrameBuffer.h"
#include "CImg.h"

#define IX(i,j,k) ((i)*_height + (j) + (k))

using namespace cimg_library;

RayFrameBuffer::RayFrameBuffer(uint8_t *frameBuffer, int width, int height) :
  _frameBuffer(frameBuffer), _width(width), _height(height)
 {}

void RayFrameBuffer::write(const char* outputfile) {
  
  CImg<unsigned char> image(this->_width, this->_height, 1, 3, 0);

  for (int i=0; i<this->_height; i++) {
    for (int j=0; j<this->_width; j++) {
      for (int k=0; k<3; k++) {
        image(i, j, 0, k) = this->_frameBuffer[ IX(i,j,k) ];
      }
    }
  }

  image.save(outputfile);

}
