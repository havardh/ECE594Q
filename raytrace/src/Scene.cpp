#include "Scene.h"
#include "Dbg.h"

#define USE_KDTREE

Scene::~Scene() {
}

void Scene::setScene(SceneIO* sio) {

  setCamera(sio->camera);
  setLights(sio->lights);
  setObjects(sio->objects);


#ifdef USE_KDTREE
  //DPRINTF("..\n");
  updateTree();
  tree.print(true);
  //DPRINTF("..\n");
#endif
}

void Scene::updateTree() {
  SurfaceAreaHeuristic sah;
  tree.setHeuristic(&sah);
  tree.setBoundingBox(computeBoundingBox());
  tree.setTerminationCondition(1024);
  tree.build(shapes, 0);
}

void Scene::setCamera(CameraIO *cio) {

  Vector position(cio->position);
  Vector direction(cio->viewDirection);
  Vector up(cio->orthoUp);
  float fov = cio->verticalFOV;
  
  this->camera = Camera(position, direction, 0, up, fov);

}

static RTLightType getLightType(LightIO *lio) {
  switch(lio->type) {
  case POINT_LIGHT: return POINT;
  case DIRECTIONAL_LIGHT: return DIRECTIONAL;
  case SPOT_LIGHT: return SPOT;
  }
  return POINT;
}

void Scene::setLights(LightIO * lio) {
  while(lio) {

    RTLightType type = getLightType(lio);
    Vector position(lio->position);
    Vector direction(lio->direction);
    RTColor color(lio->color);
    float dropOffRate = lio->dropOffRate;
    float cutOffAngle = lio->cutOffAngle;
    
    Light light(type, position, direction, color, dropOffRate, cutOffAngle);
    this->lights.push_back(light);
    lio = lio->next;
  }
}

void Scene::setObjects(ObjIO *oio) {

  while(oio) {
    RTShape* shape = RTShapeFactory::createShape(oio);
    if (shape) {
      this->shapes.push_back(shape);
    }
    oio = oio->next;
  }

}

void Scene::add(const Light light) {
  lights.push_back(light);
}

void Scene::add(RTShape *shape) {
  shapes.push_back(shape);
}

IntersectionPtr Scene::intersect(const Ray ray) {
  //DPRINTF("\n");
  
#ifdef USE_KDTREE
  return tree.intersect(ray);
#else
  std::vector<IntersectionPtr> I = intersections(ray);

  IntersectionPtr intersection(NULL);
  std::vector<IntersectionPtr>::iterator it;
  for (it = I.begin(); it != I.end(); ++it) {
    if (intersection == nullptr || *(*it) < *intersection ) {
      //DPRINTF("\n");
      intersection = *it;
    }
  }

  return intersection;
#endif
}

std::vector<IntersectionPtr> Scene::intersections(const Ray ray) {
  
  RTShapeIter it;
  std::vector<IntersectionPtr> intersections;
  for(it = shapesBegin(); it != shapesEnd(); ++it) {

    IntersectionPtr intersection = (*it)->intersect(ray);
     
    if (intersection != nullptr) {

      if (intersection->getShape()->shadeIntersection(*intersection)) {
        intersections.push_back(intersection);
      }
    }
  }

  return intersections; 

}

BoundingBox Scene::computeBoundingBox() {

  BoundingBox box;

  std::vector<RTShape*>::iterator it;
  for (it = shapes.begin(); it != shapes.end(); ++it) {
    box = box.unionWith((*it)->getBoundingBox());
  }
  
  return box;
}
