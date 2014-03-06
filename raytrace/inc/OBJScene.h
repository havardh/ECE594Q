#ifndef _OBJSCENE_H_
#define _OBJSCENE_H_

#include "Scene.h"
#include <stdio.h>
#include "tiny_obj_loader.h"
#include <vector>

class OBJScene : public Scene {

public:
  void setScene(char*);
  void setObjects(std::vector<tinyobj::shape_t> objects);
  
};

#endif /* _OBJSCENE_H_ */
