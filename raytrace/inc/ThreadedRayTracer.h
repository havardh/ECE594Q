#ifndef _THREADEDRAYTRACER_H_
#define _THREADEDRAYTRACER_H_

#include <pthread.h>
#include "RayTracer.h"

#define N 4
#define M 4

class ThreadedRayTracer : public RayTracer {

public: 
  ThreadedRayTracer(Scene *scene, RayFrameBuffer *buffer) : RayTracer(scene, buffer) {}
  virtual void renderFrame(int, int);

};

#endif /* _THREADEDRAYTRACER_H_ */
