#include <stdio.h>
#include <stdint.h>
#include "scene_io.h"
#include "RayTracer.h"
#include "ThreadedRayTracer.h"
#include "RayFrameBuffer.h"
#include "StrUtil.h"
#include "Scene.h"
#include "Timer.h"
#include "StopWatch.h"

#define USE_PTHREAD

void printLightStats(void);

int main(int argc, char *argv[]) {

  Timer t;
  StopWatch sw;
  sw.setTimer(&t);

  sw.start("Begining");

  const char *scenePath, *outputPath = "out.png";
  int width = 400, height = 400;
  if (argc < 2) {
    printf("Usage: ./raytracer <input-file> <width:height>(optional) <output-file>(optional)\n");
    exit(1);
  }
  scenePath = argv[1];
  if (argc >= 3) {
    splitWidthHeightParam(argv[2], width, height);
  }

  if (argc == 4) {
    outputPath = argv[3];
  }

  Scene scene;
  SceneIO* sceneIO = readScene(scenePath);
  sw.lap("Scene read");
  scene.setScene(sceneIO);
  sw.lap("Datastructure built");
  RayFrameBuffer fb(width, height);
  printf("..\n");
#ifdef USE_PTHREAD
  ThreadedRayTracer rayTracer(&scene, &fb);
#else
  RayTracer rayTracer(&scene, &fb);
#endif
  rayTracer.setAntiAliasingResolution(1,1);
  rayTracer.render();
  sw.lap("Scene Rendered");
  printf("wtf\n");

  fb.write(outputPath);
  sw.stop();

  sw.print();
  
  if (sceneIO != NULL) {
    deleteScene(sceneIO);
  }
  printLightStats();
  return 0;
}
