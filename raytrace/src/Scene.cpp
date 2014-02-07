#include "Scene.h"
#include "Dbg.h"

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

void Scene::setLights(LightIO * lio) {
  while(lio) {
    
    Matrix position(lio->position);
    Matrix direction(lio->direction);
    RTColor color(lio->color);
    float dropOffRate = lio->dropOffRate;
    float cutOffAngle = lio->cutOffAngle;

    Light light(position, direction, color, dropOffRate, cutOffAngle);
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

  RTShapeIter it;
  for(it = shapesBegin(); it != shapesEnd(); ++it) {

    IntersectionPtr intersection = (*it)->intersect(ray);

    if (intersection != nullptr) {
      //DPRINTF("%p\n", intersection->getShape());
      return intersection;
    }
  }

  return IntersectionPtr(NULL);

}