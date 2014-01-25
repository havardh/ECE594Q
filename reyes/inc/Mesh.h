#ifndef _MESH_H_
#define _MESH_H_

#include <stdio.h>
#include <stdint.h>
#include "Matrix.h"
#include "BoundingBox.h" 
#include "MyPolygon.h"
#include <vector>
#include "Color.h"

typedef struct {

  Matrix point;
  float u,v;

  Matrix *normal;
  Color color;

} MeshPoint;

class Mesh {

protected:
  std::vector<MeshPoint> mesh;
  int _m, _n;

public:
  Mesh(int m, int n);

  int getNumPoints() { return _m*_n; }
  int getM() { return _m; }
  int getN() { return _n; }
  Matrix & getPoint(int i);
  Matrix & getPoint(int u, int v);
  MeshPoint & getMeshPoint(int u, int v);

  Mesh & projectOnto(Matrix &);
  Mesh & transform(Matrix &);
  Mesh & homogenize();

  void generateSurfaceNormals();

  BoundingBox getBoundingBox();

  void printMesh();
};

#endif /* _MESH_H_ */
