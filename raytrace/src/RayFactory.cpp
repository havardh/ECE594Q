#include "RayFactory.h"

RayFactory::RayFactory(const Camera &camera, int width, int height) {
  _camera = camera;
  _width = width;
  _height = height;

  calculateVectors();

}

Ray RayFactory::createRay(int i, int j) {
  float sx = (float)((j + 0.5) / _width);
  float sy = (float)((i + 0.5) / _height);

  
  //printf("M: "); this->M.printPoint();
  //printf("X: "); this->X.printPoint();
  //printf("Y: "); this->Y.printPoint();
  
  Matrix P = this->M + (2 * sx - 1) * this->X + (2 * sy - 1) * this->Y;
  
  Matrix t = (P - this->E);
  Matrix D = t.normalize();
  
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

  Matrix U = _camera.getUp();
  Matrix V = _camera.getDirection();
  float phi = _camera.getFieldOfView();
  float delta = phi * ((float)_width / _height);
  float c = 1.1f;
  
  U.normalize();
  V.normalize();
  
  Matrix A = V.crossProduct(U).normalize();
  Matrix B = A.crossProduct(V).normalize();

  //printf("A: "); A.printPoint();
  //printf("B: "); B.printPoint();
  
  this->E = _camera.getPosition();
  this->X = (c * tan(delta / 2.0)) * A;
  this->Y = (c * tan(phi / 2.0)) * B;
  this->M = this->E + c*V;
    
}
