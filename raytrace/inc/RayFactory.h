#ifndef _RAYFACTORY_H_
#define _RAYFACTORY_H_

#include <vector>
#include "Ray.h"
#include "Camera.h"
#include "Matrix.h"

class RayFactory {

public:
  RayFactory(const Camera &, int, int);

  std::vector<Ray> createRays();
  Ray createRay(int i, int j);

private: 
  Camera _camera;
  int _width, _height;

  Matrix M, X, Y, E;

  void calculateVectors();

};

#endif /* _RAYFACTORY_H_ */
