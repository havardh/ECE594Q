#ifndef _PATHTRACERILLUMINATOR_H_
#define _PATHTRACERILLUMINATOR_H_

#include "Illuminator.h"
#include "Intersection.h"
#include "PathFactory.h"
#include <stdlib.h>

class PathTracerIlluminator : public Illuminator {

public:
  RTColor illuminate(Intersection);
  Illuminator* newIlluminator(ShadowTracer*, Scene*);

  virtual RTColor direct();
  virtual RTColor reflection();
  virtual RTColor refraction();

private:
  const Light* uniformlyRandomLightSource();
  int numSamplesPerPixel;
  

};

#endif /* _PATHTRACERILLUMINATOR_H_ */
