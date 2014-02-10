#ifndef _WHITTEDILLUMINATOR_H_
#define _WHITTEDILLUMINATOR_H_

#include "RTColor.h"
#include "Intersection.h"
#include "ShadowTracer.h"
#include "Light.h"
#include <cmath>

class WhittedIlluminator {
  
public:
  WhittedIlluminator(ShadowTracer *shadowTracer) 
    : _stracer(shadowTracer),
      _reflectionsComputed(0),
      _refractionCount(0),
      _scene() {}

  WhittedIlluminator(ShadowTracer *shadowTracer, Scene *scene) 
    : _stracer(shadowTracer),
      _reflectionsComputed(0),
      _refractionCount(0),
      _scene(scene) {}

  RTColor illuminate(Intersection);

  /* Local helper function for illuminate */
  RTColor ambient();
  RTColor direct();
  RTColor diffuse(const Light *light);
  RTColor specular(const Light *light);
  RTColor reflection();
  RTColor refraction();

  void setPoint(Matrix m) { point = m; }
  void setShape(RTShape *s) { shape = s; }
  void setMaterial(RTMaterial m) { material = m; }
  void setRayOrigin(Matrix m) { rayOrigin = m; }
  void setRayDirection(Matrix m) { rayDirection = m; }

private:
  ShadowTracer *_stracer;
  int _reflectionsComputed;
  int _refractionCount;
  Scene *_scene;

  /* Local shared members for helpers */
  Matrix point;
  RTShape *shape;
  RTMaterial material;
  Matrix rayOrigin;
  Matrix rayDirection;

  float computeFattj(const Light *light);

};

#endif /* _WHITTEDILLUMINATOR_H_ */
