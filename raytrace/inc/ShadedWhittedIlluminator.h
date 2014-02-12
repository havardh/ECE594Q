#ifndef _SHADEDWHITTEDILLUMINATOR_H_
#define _SHADEDWHITTEDILLUMINATOR_H_

#include "WhittedIlluminator.h"

class ShadedWhittedIlluminator : public WhittedIlluminator {

public:
  
  ShadedWhittedIlluminator(ShadowTracer *shadowTracer, Scene *scene);

  WhittedIlluminator* newIlluminator(ShadowTracer*, Scene*);

};

#endif /* _SHADEDWHITTEDILLUMINATOR_H_ */
