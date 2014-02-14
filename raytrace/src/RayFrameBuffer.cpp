#include "RayFrameBuffer.h"
#include <stdlib.h>
#include "CImg.h"

#define IX(i,j,k) ((i)*_width*3 + (j)*3 + (k))

using namespace cimg_library;

RayFrameBuffer::RayFrameBuffer(int width, int height) :
  _width(width), _height(height)
 {
   this->allocate();
}

RayFrameBuffer::~RayFrameBuffer() {
  if (this->_frameBuffer) {
    delete [] this->_frameBuffer;
  }
}

void RayFrameBuffer::allocate() {
  this->_frameBuffer = new uint8_t[_width*_height*3];

  memset(this->_frameBuffer, 0, _width*_height*3);
}

void RayFrameBuffer::set(int i, int j, int k, uint8_t value) {

  this->_frameBuffer[ IX( _height-i-1,_width-j-1,k ) ] = value;
}

uint8_t RayFrameBuffer::get(int i, int j, int k) const {
  return this->_frameBuffer[ IX( i,j,k ) ];
}

void RayFrameBuffer::write(const char* outputfile) {
  
  CImg<unsigned char> image(this->_width, this->_height, 1, 3, 0);
  
  for (int i=0; i<this->_height; i++) {
    for (int j=0; j<this->_width; j++) {
      for (int k=0; k<3; k++) {
        image(_width-j-1, i, 0, k) = this->get(i,j,k);
      }
    }
  }

  image.save(outputfile);

}
