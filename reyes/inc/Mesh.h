#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdint.h>
#include "Matrix.h"
#include "BoundingBox.h" 
#include "Polygon.h"
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

public:
  Mesh(int m, int n);

  int getNumPoints() { return _m*_n; }
  int getM() { return _m; }
  int getN() { return _n; }
  Matrix getPoint(int i);

  Mesh & projectOnto(Matrix &);
  Mesh & transform(Matrix &);
  Mesh & homogenize();

  BoundingBox getBoundingBox();

  void printMesh();
};

#endif /* _MESH_H_ */
