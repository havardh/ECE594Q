#ifndef _RTSHAPEFACTORY_H_
#define _RTSHAPEFACTORY_H_

#include "RTShape.h"
#include "RTSphere.h"
#include "RTTriangle.h"
#include "RTPolySet.h"
#include "ColorShaderRandom.h"
#include "ColorShaderIdentity.h"
#include "ColorShaderCheckerboard.h"
#include "ColorShaderGradient.h"
#include "ColorShaderTexture.h"
#include "scene_io.h"

class RTShapeFactory {
public:
  static RTShape* createShape(ObjIO*);
  static RTTriangle createTriangle(PolygonIO*, bool, bool, RTPolySet*);
  static RTMaterial createMaterial(MaterialIO*);
};

#endif /* _RTSHAPEFACTORY_H_ */
