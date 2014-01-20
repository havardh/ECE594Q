#include "FrameBuffer.h"

#include "CImg.h"
using namespace cimg_library; 

FrameBuffer::FrameBuffer(int width, int height) : _width(width), _height(height) {

  this->buffer = new Pixel[width*height];

  for (int i=0; i<width*height; i++) {
    this->buffer[i] = new Sample[1];
  }

}

FrameBuffer::~FrameBuffer() {

  for (int i=0; i<_width*_height; i++) {
    delete[] this->buffer[i];
  }

  delete [] this->buffer;

}

void FrameBuffer::setProjectionMatrix(Matrix &projectionMatrix) {

  this->_projectionMatrix = projectionMatrix;
  
}

void FrameBuffer::draw(Mesh * mesh) {

  for (int i=0; i<mesh->getNumPoints(); i++) {
    drawPoint(mesh->getPoint(i));
  }

}

void FrameBuffer::draw(Matrix * points, int n) {

  for (int i=0; i<n; i++) {
    drawPoint(points[i]);
  }
}

void FrameBuffer::drawPoint(Matrix p) {

  p.projectOnto(this->_projectionMatrix);
  p.homogenize();
  
  int x = (int)(p.get(0,0) * (float)this->_width +  (float)(this->_width/2));
  int y = (int)(p.get(1,0) * (float)this->_height + (float)(this->_height/2));
  
  if ( x < this->_width && x >= 0 && y < this->_height && y >= 0 ) {
    this->buffer[ x + this->_width * y ][0].red = 255;
    this->buffer[ x + this->_width * y ][0].green = 255;
    this->buffer[ x + this->_width * y ][0].blue = 255;
  }


}

void FrameBuffer::bind(char *filename) {
  this->_filename = filename;
}

void FrameBuffer::flush() {
  
  CImg<unsigned char> image(this->_width, this->_height, 1, 3, 0);

  for (int i=0; i<this->_height; i++) {
    for (int j=0; j<this->_width; j++) {

      image(j,_height-1-i,0,0) = this->buffer[i*this->_width + j][0].red;
      image(j,_height-1-i,0,1) = this->buffer[i*this->_width + j][0].green;
      image(j,_height-1-i,0,2) = this->buffer[i*this->_width + j][0].blue;
     
    }
  }

  image.save("out.bmp");
  
}
