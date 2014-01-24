#include "Shape.h"

#define IX(row, col) ((row) * _n + (col))

Color Shape::getColor() { 
  return _color; 
}

void Shape::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  _color.red = red; _color.green = green; _color.blue = blue; 
}

float Shape::getOpacity() { 
  return _opacity; 
}

void Shape::setOpacity(float opacity) {
  assert(opacity >= 0); assert(opacity <= 1.0);
  _opacity = opacity;
}


std::vector<Micropolygon> Shape::getMicropolygons() {
  
  std::vector<Micropolygon> polygons;

  for (int i=0; i<_m-1; i++) {
    for (int j=0; j<_n; j++) {
     
      Matrix points[4];
      points[0] = this->mesh[ (size_t)IX(i  ,j  ) ];
      points[1] = this->mesh[ (size_t)IX(i  ,(j+1)%_n) ];
      points[2] = this->mesh[ (size_t)IX(i+1,j  ) ];
      points[3] = this->mesh[ (size_t)IX(i+1,(j+1)%_n) ];

      
      Micropolygon p(points);
      p.setColor(getColor());
      p.setOpacity(getOpacity());
      
      polygons.push_back(p);
    }
  }
  
  return polygons;
}
