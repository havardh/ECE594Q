#include "FrameBuffer.h"
#include <sstream>
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

void FrameBuffer::set(int x, int y, Color color) {
  this->buffer[ x + y * this->_width ][0] = color;
}

Color FrameBuffer::get(int x, int y) const {
  return this->buffer[ x + y * this->_width][0];
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
  
  p.scale(this->_width, this->_height, 1);
  p.translate(this->_width/2, this->_height/2, 0);
  
  p.homogenize();
  
  int x = (int)(p.get(0,0));
  int y = (int)(p.get(1,0));
  
  if ( x < this->_width && x >= 0 && y < this->_height && y >= 0 ) {
    this->buffer[ x + this->_width * y ][0].red = 255;
    this->buffer[ x + this->_width * y ][0].green = 255;
    this->buffer[ x + this->_width * y ][0].blue = 255;
  }

}

void FrameBuffer::drawBox(BoundingBox box) {
  int x = (int)floor(box.getX());
  int y = (int)floor(box.getY());
  int dx = (int)ceil(box.getDX());
  int dy = (int)ceil(box.getDY());

  this->drawRectangle(x, y, dx, dy);

}

void FrameBuffer::drawMicropolygon(Micropolygon polygon) {
  BoundingBox box = polygon.getBoundingBox();
  box.projectToScreen(_width, _height);



  int x = (int)floor(box.getX());
  int y = (int)floor(box.getY());
  int dx = (int)ceil(box.getDX());
  int dy = (int)ceil(box.getDY());



  Color color = { 255, 255, 255 };
  
  for (int i=x; i < x+dx; i++) {
    for (int j=y; j < y+dy; j++) {

      float fx = (float)(i - (this->_width/2)) / (float)_width;
      float fy = (float)(j - (this->_height/2)) / (float)_height;

      if (polygon.intersects(fx, fy)) {
        
        set(j, i, color);

      }

    }
  }

}

void FrameBuffer::drawRectangle(int x, int y, int dx, int dy) {

  for (int i=y; i < y+dy; i++) {
    for (int j=x; j < x+dx; j++) {
      
      Color color = { 255, 255, 255 };
      this->set(i,j, color);

    }
  }
  
}

void FrameBuffer::bind(char *filename) {
  this->_filename = filename;
}


// Unused possible refactoring
void setPixel(CImg<unsigned char> image, int height, int j, int i, Color color) {
  image(j, height-1-i, 0, 0) = color.red;
  image(j, height-1-i, 0, 1) = color.green;
  image(j, height-1-i, 0, 2) = color.blue;
}

void FrameBuffer::flush(int i) {
  
  CImg<unsigned char> image(this->_width, this->_height, 1, 3, 0);

  for (int i=0; i<this->_height; i++) {
    for (int j=0; j<this->_width; j++) {

      Color color = get(j,i);
      
      image(j, _height-1-i, 0, 0) = color.red;
      image(j, _height-1-i, 0, 1) = color.green;
      image(j, _height-1-i, 0, 2) = color.blue;
      
    }
  }

  std::stringstream ss;
  ss << "output/" << i << ".png";
  image.save(ss.str().c_str());
  
}
