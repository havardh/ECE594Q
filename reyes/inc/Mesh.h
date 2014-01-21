#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdint.h>
#include "Matrix.h"
#include "BoundingBox.h" 
#include "Micropolygon.h"
#include <vector>

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} Color;

typedef struct {

  Matrix point;
  //Matrix normal;
  //Color color;

} MeshPoint;

class Mesh {

protected:
  std::vector<Matrix> mesh;
  int _m, _n;

public:
  Mesh(int m, int n);

  int getNumPoints() { return _m*_n; }
  Matrix getPoint(int i);

  Mesh & projectOnto(Matrix &);
  Mesh & transform(Matrix &);
  Mesh & homogenize();

  BoundingBox getBoundingBox();
  std::vector<Micropolygon> getMicropolygons();

  void printMesh();
};

#endif /* _MESH_H_ */
