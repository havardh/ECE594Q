#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(SceneIO *scene) : 
  _frameBuffer(0), _scene(scene) {

  if (_scene && _scene->camera) {
    CameraIO *cio = _scene->camera;
    Matrix position(cio->position);
    Matrix direction(cio->viewDirection);
    Matrix up(cio->orthoUp);
    float fov = cio->verticalFOV;
    
    camera = Camera(position, direction, 0, up, fov);
  } else {
    printf("Missing Camera in scene\n");
  }
  

}

RayTracer::~RayTracer(void) {
  if (_frameBuffer) {
    delete[] _frameBuffer;
  }
}


static RayColor trace(const Ray &ray) {
  (void) ray;
  return RayColor();
}

uint8_t* RayTracer::render(int width, int height) {
  _frameBuffer = new uint8_t[width*height*3];

  Matrix U = camera.getUp();
  Matrix V = camera.getDirection();
  Matrix E = camera.getPosition();
  float phi = camera.getFieldOfView();
  float delta = phi * ((float)width / height);
  float c = 2;

  U.normalize();
  V.normalize();

  Matrix A = V.crossProduct(U).normalize();
  Matrix X = A * c * tan(delta / 2.0);

  Matrix B = A.crossProduct(V).normalize();
  Matrix Y = c * tan(phi / 2.0) * B;

  Matrix M = E + c*V;

  for(int i=0; i<width; i++) {    
    for (int j=0; j<height; j++) {

      float sx = (float)((i + 0.5) / width);
      float sy = (float)((j + 0.5) / height);

      Matrix P = M + (2 * sx - 1) * X + (2 * sy - 1) * Y;

      P.printPoint();

      Ray ray;
      RayColor color = trace(ray);

      _frameBuffer[ IX(i,j,0) ] = color.red;
      _frameBuffer[ IX(i,j,1) ] = color.green;
      _frameBuffer[ IX(i,j,2) ] = color.blue;

    }
  }

  return _frameBuffer;
}
