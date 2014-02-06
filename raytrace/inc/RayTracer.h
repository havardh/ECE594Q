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
#include <stdio.h>
#include <stdint.h>
#include <vector>

class RayTracer {

private:
  RayFrameBuffer *_frameBuffer;
  Scene *_scene;
  ShadowTracer _stracer;

  std::vector<RTShape*> objects;

  Camera camera;
  std::vector<Light> lights;

  RTColor trace(const Ray ray);
  void setCamera(CameraIO*);
  void setLights(LightIO*);
  void setObjects(ObjIO*);

  bool isInShadow(const MatrixPtr point);
  bool hasOcclusion(const MatrixPtr, const Light &);

public:
  RayTracer(Scene*, RayFrameBuffer*);
  ~RayTracer(void);
  void render();
};

#endif /* _RAYTRACER_H_ */
