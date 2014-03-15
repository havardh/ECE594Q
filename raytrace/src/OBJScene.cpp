#include "OBJScene.h"
#include "OBJShapeFactory.h"

void OBJScene::setScene(char *filename) {

  std::vector<tinyobj::shape_t> tinyshapes;
  std::string err = tinyobj::LoadObj(tinyshapes, filename, "Scenes/obj/");


  printf("%s\n", err.c_str());

  this->camera = Camera(
    Vector(15, 15, -10),
    Vector(-0.8,-0.8, 0.5),
    0,
    Vector(0,1,0),
    M_PI/2
  );

  this->lights.push_back(Light(
    POINT,
    Vector(20, 5, 0),
    Vector(0,0,1),
    RTColor(1,1,1),
    0,
    0
  ));

  //this->camera = Camera(
    //  Vector(275,270,-260),
  //  Vector(0,0,1),
  //  0,
  //  Vector(0,1,0),
  //  M_PI/2
  //);
  //
     //this->lights.push_back(Light(
    //  POINT,
  //  Vector(270,500,270),
  //  Vector(0,0,1),
  //  RTColor(1,1,1),
  //  0,
  //  0
  //));

  setObjects(tinyshapes);
  
  Scene::setScene();

}

void OBJScene::setObjects(std::vector<tinyobj::shape_t> objects) {
 
  std::vector<tinyobj::shape_t>::iterator it;
  for (it = objects.begin(); it != objects.end(); ++it) {

    shapes.push_back(OBJShapeFactory::createShape(*it));

  } 
}
