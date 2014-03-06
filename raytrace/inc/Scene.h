#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include <algorithm>
#include "RTShape.h"
#include "KDTree.h"
#include "BoundingBox.h"
#include "BoundingBoxHierarchy.h"
#include "SurfaceAreaHeuristic.h"
#include "RTShapeFactory.h"
#include "Light.h"
#include "Camera.h"

class Scene {

public:
  Scene() {}
  virtual ~Scene();
  
  virtual void setScene();
  virtual void setScene(char*) = 0;
  void updateTree();

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

protected:
  Camera camera;
  std::vector<Light> lights;
  std::vector<RTShape*> shapes;
private:
  KDTree tree ;
  BoundingBoxHierarchy bbh;

  BoundingBox computeBoundingBox();
  
};

#endif /* _SCENE_H_ */

