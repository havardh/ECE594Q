#ifndef _RAYFACTORY_H_
#define _RAYFACTORY_H_

#include <vector>
#include "Ray.h"
#include "Camera.h"
#include "Vector.h"

class RayFactory {

public:
 RayFactory() : _camera(), _width(0), _height(0) {}
  RayFactory(const Camera &, int, int, int, int);

  std::vector<Ray> createRays();
  Ray createRay(int i, int j) const;
  Ray createRay(int i, int j, int k, int l) const;

private: 
  Camera _camera;
  int _width, _height, _m, _n;

  Vector M, X, Y, E;

  void calculateVectors();

};

#endif /* _RAYFACTORY_H_ */
