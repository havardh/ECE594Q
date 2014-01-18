#include "FrameBuffer.h"
#include <string.h>

FrameBuffer::FrameBuffer(int width, int height) : _width(width), _height(height) {

  this->buffer = new unsigned char[this->_width*this->_height *3];

}

FrameBuffer::~FrameBuffer() {

  delete [] this->buffer;

}

void FrameBuffer::setProjectionMatrix(Matrix &projectionMatrix) {

  this->_projectionMatrix = projectionMatrix;
  
}

void FrameBuffer::draw(Matrix * points, int n) {

  unsigned char *frameBuffer = new unsigned char[this->_width*this->_height*3];
  for (int i=0; i<n; i++) {

    //points[i].projectOnto(this->_projectionMatrix);
    //points[i].homogenize();
    
    int x = (int)(points[i].get(0,0) * (float)this->_width +  (float)(this->_width/2));
    int y = (int)(points[i].get(1,0) * (float)this->_height + (float)(this->_height/2));

    if ( x < this->_width && x >= 0 && y < this->_height && y >= 0 ) {
      frameBuffer[ x*3 + this->_width*3 * y+0 ] = 255;
      frameBuffer[ x*3 + this->_width*3 * y+1 ] = 255;
      frameBuffer[ x*3 + this->_width*3 * y+2 ] = 255;
    }
  }
  write_bmp(frameBuffer, this->_width, this->_height);

}

void FrameBuffer::bind(char *filename) {
  this->_filename = filename;
}

void FrameBuffer::flush() {
  


  //memcpy(frameBuffer, this->buffer, this->_width*this->_height*3);
  
}
