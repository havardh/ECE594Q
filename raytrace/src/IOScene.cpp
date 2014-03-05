#include "IOScene.h"

void IOScene::setScene(SceneIO* sio) {

  setCamera(sio->camera);
  setLights(sio->lights);
  setObjects(sio->objects);

  Scene::setScene();
}

void IOScene::setCamera(CameraIO *cio) {

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

void IOScene::setLights(LightIO * lio) {
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

void IOScene::setObjects(ObjIO *oio) {

  while(oio) {
    RTShape* shape = RTShapeFactory::createShape(oio);
    if (shape) {
      this->shapes.push_back(shape);
    }
    oio = oio->next;
  }

}
