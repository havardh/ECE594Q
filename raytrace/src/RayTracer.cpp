#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(SceneIO *scene, RayFrameBuffer *frameBuffer) : 
  _frameBuffer(frameBuffer), _scene(scene) {

  if (_scene && _scene->camera) {

    setCamera(_scene->camera);

    setObjects(_scene->objects);
    
  } else {
    printf("Missing Camera in scene\n");
    //exit(1);
  }
  

}

RayTracer::~RayTracer(void) {

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

RTColor RayTracer::trace(const Ray ray) {

  std::vector<RTShape*>::iterator it;
  
  for(it = objects.begin(); it != objects.end(); ++it) {
    if ((*it)->intersect(ray) != nullptr) {
      
      RTMaterial m = (*it)->getMaterial(0);
      return m.getDiffColor();
    }
  }


  return RTColor::BLACK;

}

void RayTracer::render() {

  int width = _frameBuffer->getWidth();
  int height = _frameBuffer->getHeight();

  RayFactory factory(camera, width, height);

  for(int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      Ray ray = factory.createRay(i,j);
      RTColor color = trace(ray);


      //ray.getDirection().printPoint();
      
      _frameBuffer->set(i,j,0, color.getRGBRed());
      _frameBuffer->set(i,j,1, color.getRGBGreen());
      _frameBuffer->set(i,j,2, color.getRGBBlue());

    }
  }

}
