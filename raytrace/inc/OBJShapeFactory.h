#ifndef _OBJSHAPEFACTORY_H_
#define _OBJSHAPEFACTORY_H_

#include "RTShape.h"
#include "RTPolySet.h"
#include "tiny_obj_loader.h"

class OBJShapeFactory {

public:
  static RTShape* createShape(tinyobj::shape_t);
  static RTMaterial createMaterial(tinyobj::material_t);
};

#endif /* _OBJSHAPEFACTORY_H_ */
