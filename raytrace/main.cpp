#include <stdio.h>
#include <stdint.h>
#include "scene_io.h"
#include "RayTracer.h"
#include "ThreadedRayTracer.h"
#include "RayFrameBuffer.h"
#include "Settings.h"
#include "StrUtil.h"
#include "Scene.h"
#include "Timer.h"
#include "StopWatch.h"

//#define USE_PTHREAD

void printLightStats(void);


int main(int argc, char *argv[]) {

  settings.parse(argc, argv);
  settings.print();

  //Timer t;
  //StopWatch sw;
  //sw.setTimer(&t);

  //sw.start("Begining");

  Scene scene;
  SceneIO* sceneIO = readScene(settings.input());
  //sw.lap("Scene read");
  scene.setScene(sceneIO);
  //sw.lap("Datastructure built");
  RayFrameBuffer fb(settings.width(), settings.height());
  printf("..\n");

  RayTracer *rayTracer = NULL;
  if (settings.useThreads()) {
    rayTracer = new ThreadedRayTracer(&scene, &fb);
  } else {
    rayTracer = new RayTracer(&scene, &fb);
  }

  //rayTracer.setEnvironmentMap(new EnvironmentMap("./texture/earth.jpg"));
  //
  if (settings.environmentMap()) {
    rayTracer->setEnvironmentMap(new EnvironmentMap(settings.environmentMap()));
  }
  rayTracer->setAntiAliasingResolution(settings.valias(), settings.halias());

  rayTracer->render();
  //sw.lap("Scene Rendered");
  printf("wtf\n");

  fb.write(settings.output());
  //sw.stop();

  //sw.print();
  
  if (sceneIO != NULL) {
    deleteScene(sceneIO);
  }

  delete rayTracer;
  printLightStats();
  return 0;
}
