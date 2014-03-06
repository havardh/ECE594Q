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

  void setSamplesPerPixel(int);

private:
  RTColor _illuminate(Intersection);

  const Light* uniformlyRandomLightSource();
  int numSamplesPerPixel = 10;
  bool inObject = 0;

  bool russianRoulette();

};

#endif /* _PATHTRACERILLUMINATOR_H_ */
