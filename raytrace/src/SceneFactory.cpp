#include "SceneFactory.h"

Scene* SceneFactory::load(char *filename) {

  Scene *scene;

  if (strstr(filename, ".ascii")
      || strstr(filename, ".scene") ) {
    scene = new IOScene();
  } else if (strstr(filename, ".obj")) {
    scene = new OBJScene();
  } else {
    printf("Scene type %d not supported\n", filename);
    exit(1);
  }
  
  scene->setScene(filename);
  return scene;
}
