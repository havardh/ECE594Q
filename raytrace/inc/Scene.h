#ifndef _SCENE_H_
#define _SCENE_H_

#include "scene_io.h"
#include <vector>
#include <algorithm>
#include "RTShape.h"
#include "KDTree.h"
#include "BoundingBox.h"
#include "RTShapeFactory.h"
#include "Light.h"
#include "Camera.h"

class Scene {

public:
  Scene() {}
  ~Scene();

  void setScene(SceneIO*);
  void setCamera(CameraIO*);
  void setLights(LightIO*);
  void setObjects(ObjIO*);

  void add(const Light);
  void add(RTShape*);

  size_t numLights() const { return lights.size(); }
  size_t numShapes() const { return shapes.size(); }

  Camera getCamera() const { return camera; }
  LightIter lightsBegin() const { return lights.begin(); }
  LightIter lightsEnd() const { return lights.end(); }
  RTShapeIter shapesBegin() const { return shapes.begin(); }
  RTShapeIter shapesEnd() const { return shapes.end(); }

  IntersectionPtr intersect(const Ray);
  std::vector<IntersectionPtr> intersections(const Ray);

private:
  Camera camera;
  std::vector<Light> lights;
  std::vector<RTShape*> shapes;
  KDTree tree ;

};

#endif /* _SCENE_H_ */

