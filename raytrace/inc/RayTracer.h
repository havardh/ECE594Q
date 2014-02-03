#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "Ray.h"
#include "scene_io.h"
#include "Camera.h"
#include <stdio.h>
#include <stdint.h>

class RayTracer {

private:
  uint8_t *_frameBuffer;
  SceneIO *_scene;

  Camera camera;

public:
  RayTracer(SceneIO*);
  ~RayTracer(void);
  uint8_t *render(int, int);
};

#endif /* _RAYTRACER_H_ */
