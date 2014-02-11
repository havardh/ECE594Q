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
#include "WhittedIlluminator.h"
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include "Dbg.h"

class RayTracer {

private:
  RayFrameBuffer *_frameBuffer;
  Scene *_scene;
  ShadowTracer _stracer;

  RTColor trace(const Ray ray);


public:
  RayTracer(Scene*, RayFrameBuffer*);
  void render();
};

#endif /* _RAYTRACER_H_ */
