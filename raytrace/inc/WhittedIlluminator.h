#ifndef _WHITTEDILLUMINATOR_H_
#define _WHITTEDILLUMINATOR_H_

#include "RTColor.h"
#include "Intersection.h"
#include "ShadowTracer.h"
#include "Light.h"
#include <cmath>

class WhittedIlluminator {
  
public:
  WhittedIlluminator(ShadowTracer *shadowTracer) : _stracer(shadowTracer) {}
  RTColor illuminate(Intersection);

  /* Local helper function for illuminate */
  RTColor ambient();
  RTColor direct();
  RTColor diffuse();
  RTColor specular();
  RTColor reflection();
  RTColor refraction();

  void setPoint(Matrix m) { point = m; }
  void setShape(RTShape *s) { shape = s; }
  void setMaterial(RTMaterial m) { material = m; }
  void setRayOrigin(Matrix m) { rayOrigin = m; }
  void setLightSources(std::vector<const Light*> sources) {
    lightSources = sources;
  }
  void addLightSource(const Light *source) {
    lightSources.push_back(source);
  }

private:
  ShadowTracer *_stracer;

  /* Local shared members for helpers */
  Matrix point;
  RTShape *shape;
  RTMaterial material;
  Matrix rayOrigin;
  std::vector<const Light*> lightSources;

};

#endif /* _WHITTEDILLUMINATOR_H_ */
