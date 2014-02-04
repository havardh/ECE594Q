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
    //exit(1);
  }
  

}

RayTracer::~RayTracer(void) {
  if (_frameBuffer) {
    delete[] _frameBuffer;
  }
}


static RTSphere *sphere;

static RayColor trace(const Ray &ray) {

  if (sphere->intersect(ray)) {
    return RayColor(200,200,200);
  } else {
    return RayColor(0,0,0);
  }
  

}

uint8_t* RayTracer::render(int width, int height) {
  _frameBuffer = new uint8_t[width*height*3];

  sphere = new RTSphere(Matrix(10, 0, 0), 2);

  Camera c(
    Matrix(0,0,0),
    Matrix(1,0,0),
    0,
    Matrix(0,1,0),
    (float)(M_PI/2));

  RayFactory factory(c, width, height);

  for(int i=0; i<width; i++) {    
    for (int j=0; j<height; j++) {

      Ray ray = factory.createRay(i,j);
      RayColor color = trace(ray);
      
      _frameBuffer[ IX(i,j,0) ] = color.red;
      _frameBuffer[ IX(i,j,1) ] = color.green;
      _frameBuffer[ IX(i,j,2) ] = color.blue;

    }
  }

  return _frameBuffer;
}
