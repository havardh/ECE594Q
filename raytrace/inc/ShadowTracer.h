#ifndef _SHADOWTRACER_H_
#define _SHADOWTRACER_H_

#include "Light.h"
#include <vector>
#include "Scene.h"

class ShadowTracer {

public:
  ShadowTracer() : _scene(0) {}
  ShadowTracer(Scene *scene) : _scene(scene) {}
  virtual ~ShadowTracer() {}

  virtual bool hasOcclusion(const Matrix, const Matrix*);
  virtual bool isInShadow(const Matrix* );
  virtual std::vector<const Light*> getLightSources(const Matrix *);

 private:
  Scene* _scene;

};

#endif /* _SHADOWTRACER_H_ */
