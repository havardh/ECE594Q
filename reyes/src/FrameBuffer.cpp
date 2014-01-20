#include "FrameBuffer.h"
#include "CImg.h"
using namespace cimg_library; 

FrameBuffer::FrameBuffer(int width, int height) : _width(width), _height(height) {

  this->buffer = new unsigned char[this->_width*this->_height *3];

}

FrameBuffer::~FrameBuffer() {

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

void FrameBuffer::drawPoint(Matrix p) {

  p.projectOnto(this->_projectionMatrix);
  p.homogenize();
  
  int x = (int)(p.get(0,0) * (float)this->_width +  (float)(this->_width/2));
  int y = (int)(p.get(1,0) * (float)this->_height + (float)(this->_height/2));
  
  if ( x < this->_width && x >= 0 && y < this->_height && y >= 0 ) {
    this->buffer[ x*3 + this->_width*3 * y+0 ] = 255;
    this->buffer[ x*3 + this->_width*3 * y+1 ] = 255;
    this->buffer[ x*3 + this->_width*3 * y+2 ] = 255;
  }


}

void FrameBuffer::draw(Matrix * points, int n) {

  for (int i=0; i<n; i++) {

    //points[i].projectOnto(this->_projectionMatrix);
    //points[i].homogenize();
    
    int x = (int)(points[i].get(0,0) * (float)this->_width +  (float)(this->_width/2));
    int y = (int)(points[i].get(1,0) * (float)this->_height + (float)(this->_height/2));

    if ( x < this->_width && x >= 0 && y < this->_height && y >= 0 ) {
      this->buffer[ x*3 + this->_width*3 * y+0 ] = 255;
      this->buffer[ x*3 + this->_width*3 * y+1 ] = 255;
      this->buffer[ x*3 + this->_width*3 * y+2 ] = 255;
    }
  }
}

void FrameBuffer::bind(char *filename) {
  this->_filename = filename;
}

void FrameBuffer::flush() {
  
  CImg<unsigned char> image(this->_width, this->_height, 1, 3, 0);

  for (int i=0; i<this->_height; i++) {
    for (int j=0; j<this->_width; j++) {
      for (int k=0; k<3; k++) {
        image(i,j,0,k) = this->buffer[i*this->_width*3 + j*3 + k];

      }
    }
  }

  image.save("out.bmp");
  
}
