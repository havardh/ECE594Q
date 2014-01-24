#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdint.h>
#include "Matrix.h"
#include "BoundingBox.h" 
#include "Micropolygon.h"
#include <vector>
#include "Color.h"

typedef struct {

  Matrix point;
  //Matrix normal;
  //Color color;

} MeshPoint;

class Mesh {

protected:
  std::vector<Matrix> mesh;
  int _m, _n;
  Color _color;
  float _opacity;

public:
  Mesh(int m, int n);

  int getNumPoints() { return _m*_n; }
  int getM() { return _m; }
  int getN() { return _n; }
  Matrix getPoint(int i);

  Color getColor() { return _color; }
  void setColor(uint8_t red, uint8_t green, uint8_t blue) {
    _color.red = red; _color.green = green; _color.blue = blue; 
  }
  float getOpacity() { return _opacity; }
  void setOpacity(float opacity) {
    assert(opacity >= 0); assert(opacity <= 1.0);
    _opacity = opacity;
  }

  Mesh & projectOnto(Matrix &);
  Mesh & transform(Matrix &);
  Mesh & homogenize();

  BoundingBox getBoundingBox();
  std::vector<Micropolygon> getMicropolygons();

  void printMesh();
};

#endif /* _MESH_H_ */
