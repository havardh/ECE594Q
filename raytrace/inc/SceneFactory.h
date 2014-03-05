#ifndef _SCENEFACTORY_H_
#define _SCENEFACTORY_H_

#include "Scene.h"
#include "IOScene.h"
#include "OBJScene.h"

class SceneFactory {

public:
  static Scene* load(char*);

};

#endif /* _SCENEFACTORY_H_ */
