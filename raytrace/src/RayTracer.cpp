#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(SceneIO *scene) : 
  _frameBuffer(0), _scene(scene) {

  if (_scene && _scene->camera) {

    setCamera(_scene->camera);

    setObjects(_scene->objects);
    
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

void RayTracer::setCamera(CameraIO *cio) {

  Matrix position(cio->position);
  Matrix direction(cio->viewDirection);
  Matrix up(cio->orthoUp);
  float fov = cio->verticalFOV;
  
  camera = Camera(position, direction, 0, up, fov);

}

void RayTracer::setObjects(ObjIO *oio) {

  while(oio) {
    RTShape* shape = RTShapeFactory::createShape(oio);
    if (shape) {
      printf( "obj\n" );

      if (typeid(*shape) == typeid(RTTriangle)) {
        printf("triangle"); ((RTTriangle*)shape)->getP0().printPoint();
      } else if (typeid(*shape) == typeid(RTSphere)) {
        printf("sphere"); ((RTSphere*)shape)->getOrigin().printPoint();
      }
      objects.push_back(shape);
    }
    oio = oio->next;
  }

}

RayColor RayTracer::trace(const Ray &ray) {

  std::vector<RTShape*>::iterator it;
  
  for(it = objects.begin(); it != objects.end(); ++it) {
    if ((*it)->intersect(ray)) {
      return RayColor(200,200,200);
    }
  }

  return RayColor(0,0,0);

}

uint8_t* RayTracer::render(int width, int height) {
  _frameBuffer = new uint8_t[width*height*3];

  RayFactory factory(camera, width, height);

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
