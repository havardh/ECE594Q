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

private:
  ShadowTracer *_stracer;

};

#endif /* _WHITTEDILLUMINATOR_H_ */
