#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Ray.h"
#include "scene_io.h"
#include "Camera.h"
#include "RayFactory.h"
#include "RTSphere.h"
#include "RTShape.h"
#include "RTShapeFactory.h"
#include <stdio.h>
#include <stdint.h>
#include <vector>

class RayTracer {

private:
  uint8_t *_frameBuffer;
  SceneIO *_scene;

  std::vector<RTShape*> objects;

  Camera camera;

  RayColor trace(const Ray &ray);
  void setCamera(CameraIO*);
  void setObjects(ObjIO*);

public:
  RayTracer(SceneIO*);
  ~RayTracer(void);
  uint8_t *render(int, int);
};

#endif /* _RAYTRACER_H_ */
