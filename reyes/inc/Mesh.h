#ifndef _MESH_H_
#define _MESH_H_

#include <stdint.h>
#include "Matrix.h"

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
  MeshPoint *mesh;
  int _m, _n;

public:
  Mesh();
  ~Mesh();
};

#endif /* _MESH_H_ */
