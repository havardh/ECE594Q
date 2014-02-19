#ifndef _RAYFACTORY_H_
#define _RAYFACTORY_H_

#include <vector>
#include "Ray.h"
#include "Camera.h"
#include "Vector.h"

class RayFactory {

public:
 RayFactory() : _camera(), _width(0), _height(0) {}
  RayFactory(const Camera &, int, int);

  std::vector<Ray> createRays();
  Ray createRay(int i, int j) const;

private: 
  Camera _camera;
  int _width, _height;

  Vector M, X, Y, E;

  void calculateVectors();

};

#endif /* _RAYFACTORY_H_ */
