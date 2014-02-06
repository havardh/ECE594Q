#ifndef _SHADOWTRACER_H_
#define _SHADOWTRACER_H_


#include "Scene.h"

class ShadowTracer {

 public:
 ShadowTracer(Scene *scene) : _scene(scene) {}

  bool hasOcclusion(const Matrix, const Matrix*);
  bool isInShadow(const Matrix* point);

 private:
  Scene* _scene;

};

#endif /* _SHADOWTRACER_H_ */
