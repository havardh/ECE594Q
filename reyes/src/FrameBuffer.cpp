#include "FrameBuffer.h"
#include "CImg.h"
#include "assert.h"

#ifndef CPPUTEST
#include <sstream>
#endif

using namespace cimg_library; 

FrameBuffer::FrameBuffer(int width, int height) : _width(width), _height(height) {


  std::vector<ZBuffer> initial(4*4);
  pixels = std::vector<std::vector<ZBuffer> >((size_t)(width*height), initial);
  

}

FrameBuffer::~FrameBuffer() {}

void FrameBuffer::set(int x, int y, Color color) {

  assert(x >= 0);
  assert(y >= 0);
  assert(x < _width);
  assert(y < _height);
  
  for (int i=0; i<4*4; i++) {
    Sample s = { 1.0, 1.0, color };
    pixels[(size_t)(x + y *this->_width)][(size_t)i].add(s);
  }
}

void FrameBuffer::set(int x, int y, int i, Color color, float z) {
  assert( z >= 0 );
  assert( z <= 1 );

  Sample s = { z, 1.0, color };
  pixels[(size_t)(x + y *this->_width)][(size_t)i].add(s);

}

void FrameBuffer::set(int x, int y, int i, Color color, float z, float opacity) {

  assert(x >= 0);
  assert(x < _width);
  assert(y >= 0);
  assert(y < _height);
  assert(i >= 0);
  assert(i < 4*4);

  Sample s = { z, opacity, color };
  pixels[(size_t)(x + y *this->_width)][(size_t)i].add(s);

}

void FrameBuffer::set(int x, int y, int i, Color color) {

  Sample s = { 1.0, 1.0, color };
  pixels[(size_t)(x + y *this->_width)][(size_t)i].add(s);

}

Color FrameBuffer::get(int x, int y) const {
  assert(x < _width);
  assert(y < _height);

  int red = 0, green = 0, blue = 0;
  for (int i=0; i<4*4; i++) {
    
    ZBuffer zBuffer = pixels[(size_t)(x + y *this->_width)][(size_t)i];
    Color c = zBuffer.getColor();

    red += c.red;
    green += c.green;
    blue += c.blue;
  }

  Color c = { 
    (uint8_t)(red / (4*4)), 
    (uint8_t)(green / (4*4)), 
    (uint8_t)(blue / (4*4)) 
  };
  return c;
}

void FrameBuffer::setProjectionMatrix(Matrix &projectionMatrix) {

  this->_projectionMatrix = projectionMatrix;
  
}

void FrameBuffer::draw(Mesh * mesh) {

  for (int i=0; i<mesh->getNumPoints(); i++) {   
    draw(mesh->getPoint(i));
  }

}

void FrameBuffer::draw(Matrix * points, int n) {

  for (int i=0; i<n; i++) {
    draw(points[i]);
  }
}

void FrameBuffer::draw(Shape & shape) {

  //draw(&shape);

  std::vector<Micropolygon> polygons = shape.getMicropolygons();
  std::vector<Micropolygon>::iterator it;
  for (it = polygons.begin(); it != polygons.end(); ++it) {
    draw(*it);
  }

}

void FrameBuffer::draw(Matrix p) {
  
  p.translate(1, 1, 0);
  p.scale(_width/2, _height/2, 1);
  
  p.homogenize();
  
  int x = (int)(p.get(0,0));
  int y = (int)(p.get(1,0));
  
  if ( x < this->_width && x >= 0 && y < this->_height && y >= 0 ) {
    Color c = { 255, 255, 255 };
    set(x, y, c);
  }
}

void FrameBuffer::draw(BoundingBox box) {
  int x = (int)floor(box.getX());
  int y = (int)floor(box.getY());
  int dx = (int)ceil(box.getDX());
  int dy = (int)ceil(box.getDY());

  this->draw(x, y, dx, dy);

}

void FrameBuffer::draw(Micropolygon polygon) {
  BoundingBox box = polygon.getBoundingBox();
  box.projectToScreen(_width, _height);

  int x = (int)floor(box.getX());
  int y = (int)floor(box.getY());
  int dx = (int)ceil(box.getDX());
  int dy = (int)ceil(box.getDY());
  
  // pixel size in -1 - 1 range divided by number of samples
  float fdx = (2.0f / _width) / 4.0f;
  float fdy = (2.0f / _height) / 4.0f;

  for (int i=x; i < x+dx && i <_width; i++) {
    for (int j=y; j < y+dy && j < _height; j++) {
      if (i > 0 && j > 0) {
        // Back to eye-space
        float fx = (float)(2*i / (float)_width)-1;
        float fy = (float)(2*j / (float)_height)-1;
        
        for (int k=0; k<4; k++) {
          for (int l=0; l<4; l++) {
            
            if (polygon.intersects(fx + k*fdx, fy + l*fdy)) {

              set(i, j, k*4+l, polygon.getColor(), polygon.get(0).get(2), polygon.getOpacity());
            }
          }
        }
      }
    }
  }
}

void FrameBuffer::draw(int x, int y, int dx, int dy) {

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

void FrameBuffer::flush(int fileNumber) {
  (void) fileNumber;
  CImg<unsigned char> image(this->_width, this->_height, 1, 3, 0);


  for (int i=0; i<this->_height; i++) {
    for (int j=0; j<this->_width; j++) {

      Color color = get(j,i);
      
      image(j, _height-1-i, 0, 0) = color.red;
      image(j, _height-1-i, 0, 1) = color.green;
      image(j, _height-1-i, 0, 2) = color.blue;
      
    }
  }

#ifndef CPPUTEST
  std::stringstream ss;
  ss << "output/" << fileNumber << ".png";
  image.save(ss.str().c_str());
#endif
  
}

void FrameBuffer::clear() {
  
}
