#ifndef _IOSCENE_H_
#define _IOSCENE_H_

#include "scene_io.h"
#include "Scene.h"

class IOScene : public Scene {

public:
  void setScene(char*);
  void setScene(SceneIO*);
  void setCamera(CameraIO*);
  void setLights(LightIO*);
  void setObjects(ObjIO*);

};

#endif /* _IOSCENE_H_ */
