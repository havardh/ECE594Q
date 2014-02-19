#include <stdio.h>
#include <stdint.h>
#include "scene_io.h"
#include "RayTracer.h"
#include "ThreadedRayTracer.h"
#include "RayFrameBuffer.h"
#include "StrUtil.h"
#include "Scene.h"

int main(int argc, char *argv[]) {

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
  scene.setScene(sceneIO);
  RayFrameBuffer fb(width, height);

  ThreadedRayTracer rayTracer(&scene, &fb);
  rayTracer.render();
  fb.write(outputPath);
  
  if (sceneIO != NULL) {
    deleteScene(sceneIO);
  }
  
  return 0;
}
