#ifndef _WHITTEDILLUMINATOR_H_
#define _WHITTEDILLUMINATOR_H_

#include "RTColor.h"
#include "Intersection.h"
#include "ShadowTracer.h"
#include "Light.h"

class WhittedIlluminator {
  
public:
  WhittedIlluminator(ShadowTracer *shadowTracer) : _stracer(shadowTracer) {}
  RTColor illuminate(IntersectionPtr i);

private:
  ShadowTracer *_stracer;

};

#endif /* _WHITTEDILLUMINATOR_H_ */
