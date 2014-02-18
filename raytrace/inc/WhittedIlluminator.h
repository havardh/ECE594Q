#ifndef _WHITTEDILLUMINATOR_H_
#define _WHITTEDILLUMINATOR_H_

#include "RTColor.h"
#include "Intersection.h"
#include "ShadowTracer.h"
#include "Snell.h"
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
  virtual RTColor ambient();
  virtual RTColor direct();
  virtual RTColor diffuse(const Light *light);
  virtual RTColor specular(const Light *light);
  virtual RTColor reflection();
  virtual RTColor refraction();

  void setScene(Scene *s) { _scene = s; }

  void setPoint(Vector m) { point = m; }
  void setShape(RTShape *s) { shape = s; }
  void setMaterial(RTMaterial m) { material = m; }
  void setRayOrigin(Vector m) { rayOrigin = m; }
  void setRayDirection(Vector m) { rayDirection = m; }

  // Used to create new illuminator for reflection and refraction
  WhittedIlluminator* newIlluminator(ShadowTracer*, Scene*);

protected:
  /* Local shared members for helpers */
  Vector point;
  RTShape *shape;
  RTMaterial material;
  Vector rayOrigin;
  Vector rayDirection;

  virtual void setLocalVariables(Intersection);

private:
  ShadowTracer *_stracer;
  int _reflectionsComputed;
  int _refractionCount;
  Scene *_scene;

  bool isGoingIntoObject();
  float computeFattj(const Light *light);

};

#endif /* _WHITTEDILLUMINATOR_H_ */
