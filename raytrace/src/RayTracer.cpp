#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(Scene *scene, RayFrameBuffer *frameBuffer) : 
  _frameBuffer(frameBuffer), _scene(scene), _stracer(scene) {
  
}

RayTracer::~RayTracer(void) {

}

RTColor RayTracer::trace(const Ray ray) {

  IntersectionPtr intersection = _scene->intersect(ray);
 
  WhittedIlluminator illuminator(&_stracer);
  if (intersection != nullptr) {
    RTShape *shape = intersection->getShape();

    if (shape) {
      return illuminator.illuminate(*intersection);

    }
  }

  return RTColor::BLACK;

}

void RayTracer::render() {

  int width = _frameBuffer->getWidth();
  int height = _frameBuffer->getHeight();

  RayFactory factory(_scene->getCamera(), width, height);

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
