#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(Scene *scene, RayFrameBuffer *frameBuffer) : 
  _frameBuffer(frameBuffer), _scene(scene), _stracer(scene) {
}

RTColor RayTracer::trace(const Ray ray) {


  IntersectionPtr intersection = _scene->intersect(ray);
  
  ShadedWhittedIlluminator illuminator(&_stracer, _scene);
  if (intersection != nullptr) {
    RTShape *shape = intersection->getShape();
    
    if (shape) {
      return illuminator.illuminate(*intersection);

    }
  }

  return RTColor::BLACK;

}

void RayTracer::renderPixel(int i, int j) {

  Ray ray = _factory.createRay(i,j);
  RTColor color = trace(ray);
  
  _frameBuffer->set(i,j,0, color.getRGBRed());
  _frameBuffer->set(i,j,1, color.getRGBGreen());
  _frameBuffer->set(i,j,2, color.getRGBBlue());

}

void RayTracer::renderFrame(int width, int height) {

  for(int i=0; i<height; i++) {
    for (int j=0; j<width; j++) {
      renderPixel(i,j);
    }
  }

}

void RayTracer::render() {

  int width = _frameBuffer->getWidth();
  int height = _frameBuffer->getHeight();

  _factory = RayFactory(_scene->getCamera(), width, height);

  renderFrame(width, height);

}
