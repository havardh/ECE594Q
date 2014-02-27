#ifndef _WHITTEDILLUMINATOR_H_
#define _WHITTEDILLUMINATOR_H_

#include "RTColor.h"
#include "Intersection.h"
#include "ShadowTracer.h"
#include "Illuminator.h"
#include "Snell.h"
#include "Light.h"
#include <cmath>

class WhittedIlluminator : public Illuminator {
  
 public:
 WhittedIlluminator() {
    setShadowTracer(0);
    setScene(0);
  }
  WhittedIlluminator(ShadowTracer *shadowTracer) {
    setShadowTracer(shadowTracer);
    setScene(0);
  }

 WhittedIlluminator(ShadowTracer *shadowTracer, Scene *scene) {
    setShadowTracer(shadowTracer);
    setScene(scene);
  }

  RTColor illuminate(Intersection);

  /* Local helper function for illuminate */
  virtual RTColor ambient();
  virtual RTColor direct();
  virtual RTColor diffuse(const Light *light);
  virtual RTColor specular(const Light *light);
  virtual RTColor reflection();
  virtual RTColor refraction();

  // Used to create new illuminator for reflection and refraction
  virtual WhittedIlluminator* newIlluminator(ShadowTracer*, Scene*);

  virtual void setLocalVariables(Intersection);

 private:
  bool isGoingIntoObject();

};

#endif /* _WHITTEDILLUMINATOR_H_ */
