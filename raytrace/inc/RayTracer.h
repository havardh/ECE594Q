#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Ray.h"
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "RayFactory.h"
#include "RTSphere.h"
#include "RTShape.h"
#include "RTShapeFactory.h"
#include "RTColor.h"
#include "RayFrameBuffer.h"
#include "ShadowTracer.h"
#include "Illuminator.h"
#include "WhittedIlluminator.h"
#include "PathTracerIlluminator.h"
#include "ShadedWhittedIlluminator.h"
#include "ProgressBar.h"
#include "Settings.h"
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include "Dbg.h"

class RayTracer {

private:
  RayFrameBuffer *_frameBuffer;
  Scene *_scene;
  ShadowTracer _stracer;
  EnvironmentMap *_environmentMap = 0;
  int _m, _n;

  RTColor trace(const Ray ray);

protected:
  RayFactory _factory;

public:
  RayTracer(Scene*, RayFrameBuffer*);
  virtual void renderFrame(int, int);
  void renderPixel(int, int);
  void render();
  void setAntiAliasingResolution(int,int);
  void setEnvironmentMap(EnvironmentMap *map) { _environmentMap = map; }
  

};

#endif /* _RAYTRACER_H_ */
