#include "Shape.h"

#define IX(row, col) ((row) * _m + (col))

Color Shape::getColor() {
  return getMeshPoint(0,0).color;
}

void Shape::setColor(uint8_t red, uint8_t green, uint8_t blue) {
  Color c = { red, green, blue };
  for (int i=0; i<_m; i++) {
    for (int j=0; j<_n; j++) {
      getMeshPoint(i,j).color = c;
    }
  }
}

float Shape::getOpacity() { 
  return _opacity; 
}

void Shape::setOpacity(float opacity) {
  assert(opacity >= 0); assert(opacity <= 1.0);
  _opacity = opacity;
}


std::vector<Polygon> Shape::getPolygons() {
  
  std::vector<Polygon> polygons;

  for (int i=0; i<_m-1; i++) {
    for (int j=0; j<_n; j++) {
     
      Matrix points[4];
      points[0] = this->getPoint(IX(i  ,j  ));
      points[1] = this->getPoint(IX(i  ,(j+1)%_n));
      points[2] = this->getPoint(IX(i+1,j  ));
      points[3] = this->getPoint(IX(i+1,(j+1)%_n));

      Polygon p(points);
      p.setColor(getMeshPoint(i,j).color);
      p.setOpacity(getOpacity());
      
      polygons.push_back(p);
    }
  }
  
  return polygons;
}

void Shape::shade(ShaderFunction shader) {

  if (shader != NULL) {

    for (int i=0; i<_m; i++) {
      for (int j=0; j<_n; j++) {
        ShaderParam param = { 
          (float)i/(_m-1) ,
          (float)j/(_n-1), 
          &getMeshPoint(i,j) };
        (*shader)(param);
      }
    }

  }
}
