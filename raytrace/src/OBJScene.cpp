#include "OBJScene.h"
#include "OBJShapeFactory.h"
#include <iostream>

void OBJScene::setScene(char *filename) {

  std::vector<tinyobj::shape_t> tinyshapes;
  std::string err = tinyobj::LoadObj(tinyshapes, filename, "../lib/tinyobjloader/");

  std::cout << err << std::endl;

  this->camera = Camera(
    Vector(200,0,0),
    Vector(-1,0,0),
    0,
    Vector(0,1,0),
    M_PI/4
  );

  this->lights.push_back(Light(
    POINT,
    Vector(270,500,270),
    Vector(0,0,1),
    RTColor(1,1,1),
    0,
    0
  ));

  setObjects(tinyshapes);

  Scene::setScene();

}

void OBJScene::setObjects(std::vector<tinyobj::shape_t> objects) {
 
  std::vector<tinyobj::shape_t>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it) {

    shapes.push_back(OBJShapeFactory::createShape(*it));

  } 
}
