#include "RayFactory.h"
#include "Dbg.h"

RayFactory::RayFactory(const Camera &camera, int width, int height, int m, int n) {
  _camera = camera;
  _width = width;
  _height = height;
  _m = m;
  _n = n;

  calculateVectors();

}

Ray RayFactory::createRay(int i, int j) const {
  return createRay(i,j,0,0);
}

Ray RayFactory::createRay(int i, int j, int k, int l) const{

  

  float sx = (float)((j + (k/(float)_m) + ((1.0/_m)/2)) / _width);
  float sy = (float)((i + (l/(float)_n) + ((1.0/_n)/2)) / _height);

  
  //printf("M: "); this->M.printPoint();
  //printf("X: "); this->X.printPoint();
  //printf("Y: "); this->Y.printPoint();
  
  Vector P = this->M + (2 * sx - 1) * this->X + (2 * sy - 1) * this->Y;
  
  Vector t = (P - this->E);
  Vector D = t.normalize();
  
  return Ray(this->E, D);
}

std::vector<Ray> RayFactory::createRays() {
  std::vector<Ray> rays;

 
  for (int i=0; i<_height; i++) {
    for (int j=0; j<_width; j++) {

      Ray ray = createRay(i,j);
      rays.push_back(ray);
    }
  }

  return rays;
}

void RayFactory::calculateVectors() {

  Vector U = _camera.getUp();
  Vector V = _camera.getDirection();
  float phi = _camera.getFieldOfView();
  float delta = phi * ((float)_width / _height);
  float c = 1.1;
  
  U.normalize();
  V.normalize();
  
  Vector A = V.cross(U).normalize();
  Vector B = A.cross(V).normalize();
  
  this->E = _camera.getPosition();
  this->X = (c * tan(delta / 2.0)) * A;
  this->Y = (c * tan(phi / 2.0)) * B;
  this->M = this->E + c*V;
  
}
