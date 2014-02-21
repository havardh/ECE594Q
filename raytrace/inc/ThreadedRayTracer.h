#ifndef _THREADEDRAYTRACER_H_
#define _THREADEDRAYTRACER_H_

#include <pthread.h>
#include "RayTracer.h"

#define N 8
#define M 8

class ThreadedRayTracer : public RayTracer {

public: 
  ThreadedRayTracer(Scene *scene, RayFrameBuffer *buffer) : RayTracer(scene, buffer) {}
  virtual void renderFrame(int, int);

};

#endif /* _THREADEDRAYTRACER_H_ */
