#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "Color.h"
#include "Mesh.h"
#include "Shader.h"
#include <assert.h>

class Shape : public Mesh {

private:
  float _opacity;

public:
  
 Shape() : Mesh(10,10), _opacity(0) {
    setColor(255, 255, 255);
  }

  Shape(int m, int n) : Mesh(m,n), _opacity(0) {
    setColor(255, 255, 255);
  }

  std::vector<MyPolygon> getMyPolygons();

  Color getColor();
  void setColor(uint8_t, uint8_t, uint8_t);
  float getOpacity();
  void setOpacity(float);
  void shade(ShaderFunction);

};

#endif /* _SHAPE_H_ */
