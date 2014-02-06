#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(SceneIO *scene, RayFrameBuffer *frameBuffer) : 
  _frameBuffer(frameBuffer), _scene(scene) {

  if (_scene && _scene->camera) {

    setCamera(_scene->camera);
    setLights(_scene->lights);
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

void RayTracer::setLights(LightIO * lio) {
  while(lio) {
    
    Matrix position(lio->position);
    Matrix direction(lio->direction);
    RTColor color(lio->color);
    float dropOffRate = lio->dropOffRate;
    float cutOffAngle = lio->cutOffAngle;

    Light light(position, direction, color, dropOffRate, cutOffAngle);
    lights.push_back(light);

    lio = lio->next;
  }
}

void RayTracer::setObjects(ObjIO *oio) {

  while(oio) {
    RTShape* shape = RTShapeFactory::createShape(oio);
    if (shape) {
      objects.push_back(shape);
    }
    oio = oio->next;
  }

}

bool RayTracer::hasOcclusion(const MatrixPtr point, const Light & light) {
  (void) point; (void) light;
  return true;
}

bool RayTracer::isInShadow(const MatrixPtr point) {

  std::vector<Light>::iterator it;
  for (it = lights.begin();
       it != lights.end();
       ++it) {

    if (!hasOcclusion(point, *it)) {
      return false;
    }
  }

  return true;
}

RTColor RayTracer::trace(const Ray ray) {

  std::vector<RTShape*>::iterator it;
  
  for(it = objects.begin(); it != objects.end(); ++it) {

    MatrixPtr intersection = (*it)->intersect(ray);
    if (intersection != nullptr) {
      RTMaterial m = (*it)->getMaterial(0);
      
      RTColor color = m.getAmbColor();
      if (!isInShadow(intersection)) {
        color = m.getDiffColor();
      }
      
      return color;
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
