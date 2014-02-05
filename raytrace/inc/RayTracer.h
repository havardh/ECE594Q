#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Ray.h"
#include "scene_io.h"
#include "Camera.h"
#include "RayFactory.h"
#include "RTSphere.h"
#include "RTShape.h"
#include "RTShapeFactory.h"
#include "RTColor.h"
#include "RayFrameBuffer.h"
#include <stdio.h>
#include <stdint.h>
#include <vector>

class RayTracer {

private:
  RayFrameBuffer *_frameBuffer;
  SceneIO *_scene;

  std::vector<RTShape*> objects;

  Camera camera;

  RTColor trace(const Ray &ray);
  void setCamera(CameraIO*);
  void setObjects(ObjIO*);

public:
  RayTracer(SceneIO*, RayFrameBuffer*);
  ~RayTracer(void);
  void render();
};

#endif /* _RAYTRACER_H_ */
