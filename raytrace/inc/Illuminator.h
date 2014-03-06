#ifndef _ILLUMINATOR_H_
#define _ILLUMINATOR_H_

// Constants used for computing light falloff
#define C1 0.25f
#define C2 0.1f
#define C3 0.001f

#include "EnvironmentMap.h"
#include "Intersection.h"
#include "ShadowTracer.h"
#include "Scene.h"
#include "Dbg.h"

class Illuminator {
  
public:
  Illuminator() : _reflectionsComputed(0), _refractionCount(0) {}
  virtual ~Illuminator();
  virtual RTColor illuminate(Intersection) = 0;
  virtual Illuminator* newIlluminator(ShadowTracer*, Scene*) = 0;
  
  void setShadowTracer(ShadowTracer *stracer) { 
    _stracer = stracer; 
  }
  void setScene(Scene *scene) { _scene = scene; }

  ShadowTracer* getShadowTracer() { 
    return _stracer; 
  }
  Scene* getScene() { return _scene; }
  Intersection getIntersection() { return _intersection; }

  virtual RTColor ambient();
  virtual RTColor diffuse(const Light *light);
  virtual RTColor specular(const Light *light);

  void setPoint(Vector m) { point = m; }
  void setShape(RTShape *s) { shape = s; }
  void setMaterial(RTMaterial m) { material = m; }
  void setRayOrigin(Vector m) { rayOrigin = m; }
  void setRayDirection(Vector m) { rayDirection = m; }
  void setIntersection(Intersection i) { _intersection = i; }

  int reflectionsComputed() { return _reflectionsComputed; }
  int refractionCount() { return _refractionCount; }
  int incrementReflectionComputed() { return _reflectionsComputed++; }
  int incrementRefractionCount() { return _refractionCount++; }
  int decrementRefractionCount() { return _refractionCount--; }
  void setReflectionsComputed(int r) { _reflectionsComputed = r; }
  void setRefractionCount(int c) { _refractionCount = c; }

  void setEnvironmentMap(EnvironmentMap *map) { _environmentMap = map; }
  EnvironmentMap *getEnvironmentMap() { return _environmentMap; }

protected:

  /* Local shared members for helpers */
  Vector point;
  RTShape *shape;
  RTMaterial material;
  Vector rayOrigin;
  Vector rayDirection;
  Intersection _intersection;

  virtual void setLocalVariables(Intersection);
  virtual float computeFattj(const Light *light);

private:

  EnvironmentMap *_environmentMap  = 0;
  ShadowTracer *_stracer = 0;
  Scene *_scene = 0;

  int _reflectionsComputed;
  int _refractionCount;
  
};

#endif /* _ILLUMINATOR_H_ */
