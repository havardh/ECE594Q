#ifndef _SHADOWTRACER_H_
#define _SHADOWTRACER_H_

#include "Light.h"
#include <vector>
#include "Scene.h"

class ShadowTracer {

public:
  ShadowTracer() : _scene() {}
  ShadowTracer(Scene *scene) : _scene(scene) {}
  virtual ~ShadowTracer() {}

  virtual bool hasOcclusion(const Vector, const Vector*);
  virtual std::vector<const Light*> getLightSources(const Vector *);

  virtual RTColor shadowFactor(const Vector&, const Light*);

 private:
  Scene* _scene;

};

#endif /* _SHADOWTRACER_H_ */
