#include "Scene.h"
#include "Dbg.h"

Scene::~Scene() {
}

void Scene::setScene(SceneIO* sio) {

  setCamera(sio->camera);
  setLights(sio->lights);
  setObjects(sio->objects);

}

void Scene::setCamera(CameraIO *cio) {

  Matrix position(cio->position);
  Matrix direction(cio->viewDirection);
  Matrix up(cio->orthoUp);
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
    Matrix position(lio->position);
    Matrix direction(lio->direction);
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

  std::vector<IntersectionPtr> I = intersections(ray);

  IntersectionPtr intersection(NULL);
  std::vector<IntersectionPtr>::iterator it;
  for (it = I.begin(); it != I.end(); ++it) {
    if (intersection == nullptr || *(*it) < *intersection ) {
      intersection = *it;
    }
  }

  return intersection;
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
