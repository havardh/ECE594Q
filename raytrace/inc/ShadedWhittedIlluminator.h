#ifndef _SHADEDWHITTEDILLUMINATOR_H_
#define _SHADEDWHITTEDILLUMINATOR_H_

#include "WhittedIlluminator.h"

class ShadedWhittedIlluminator : public WhittedIlluminator {

public:
  ShadedWhittedIlluminator(ShadowTracer *stracer, Scene *scene) :
    WhittedIlluminator(stracer, scene) {}

  WhittedIlluminator* newIlluminator(ShadowTracer*, Scene*);

  void setLocalVariables(Intersection intersection);

};

#endif /* _SHADEDWHITTEDILLUMINATOR_H_ */
