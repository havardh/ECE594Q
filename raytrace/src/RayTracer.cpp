#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(Scene *scene, RayFrameBuffer *frameBuffer) : 
  _frameBuffer(frameBuffer), _scene(scene), _stracer(scene) {
  
}

RayTracer::~RayTracer(void) {

}

bool RayTracer::hasOcclusion(const MatrixPtr point, const Light & light) {
  (void) point; (void) light;
  return false;
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

  MatrixPtr intersection = _scene->intersect(ray);
  if (intersection != nullptr) {
    return RTColor::WHITE;
  }

  /*std::vector<RTShape*>::iterator it;
  
  for(it = objects.begin(); it != objects.end(); ++it) {

    MatrixPtr intersection = (*it)->intersect(ray);
    if (intersection != nullptr) {
      printf("%intersected\n");
      RTMaterial m = (*it)->getMaterial(0);
      
      RTColor color = m.getAmbColor();
      if (!isInShadow(intersection)) {
        color = m.getDiffColor();
      }
      
      return color;
    }
    }*/

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
