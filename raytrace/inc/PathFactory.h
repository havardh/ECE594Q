#ifndef _PATHFACTORY_H_
#define _PATHFACTORY_H_

#include "Ray.h"
#include "Intersection.h"

class PathFactory {

public:
  static Ray createPath(Intersection);

};

#endif /* _PATHFACTORY_H_ */
