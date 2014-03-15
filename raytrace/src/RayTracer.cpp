#include "RayTracer.h"

#define IX(i,j,k) ((i)*height + (j) + (k))

RayTracer::RayTracer(Scene *scene, RayFrameBuffer *frameBuffer) : 
  _frameBuffer(frameBuffer), _scene(scene), _stracer(scene), _m(1), _n(1) {
}

RTColor RayTracer::trace(const Ray ray) {
  //DPRINTF(""); ray.getDirection().print();
  //static int i=0; DPRINTF("%d\n", i++);
  IntersectionPtr intersection = _scene->intersect(ray);
  //ShadedWhittedIlluminator illuminator(&_stracer, _scene);
  PathTracerIlluminator illuminator;
  illuminator.setSamplesPerPixel(settings.numSamples());
  illuminator.setShadowTracer(&_stracer);
  illuminator.setScene(_scene);
  illuminator.setEnvironmentMap(_environmentMap);

  if (intersection != nullptr) {
    RTShape *shape = intersection->getShape();
    
    if (shape) {
      return illuminator.illuminate(*intersection);
    }
  } else {
    if (_environmentMap) {
      //ray.getDirection().print();
      return _environmentMap->get(ray);

    }
  }

  return RTColor(0,0,0);

}

void RayTracer::renderPixel(int i, int j) {
  
  //if (!(i > 40 && i < 60 && j > 40 && j < 60)) return;
  //if (i != 50 || j != 25) return;

  if (settings.progress()) {
    ProgressBar_tick();
  }


  RTColor color(0,0,0);
  for (int k=0; k<_m; k++) {
    for (int l=0; l<_n; l++) {
      Ray ray = _factory.createRay(i,j, k, l);
      color += trace(ray) * (1.0/(_m*_n));
    }
  }

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

  if (settings.progress()) {
    ProgressBar_setMax(width*height);
  }

  _factory = RayFactory(_scene->getCamera(), width, height, _m, _n);

  renderFrame(width, height);

}

void RayTracer::setAntiAliasingResolution(int m, int n) {
  _m = m; _n = n;
}
