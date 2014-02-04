#include <stdio.h>
#include <stdint.h>
#include "scene_io.h"
#include "RayTracer.h"
#include "RayFrameBuffer.h"
#include "StrUtil.h"

int main(int argc, char *argv[]) {

  const char *scenePath, *outputPath = "out.png";
  int width = 200, height = 200;
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

  SceneIO *scene = readScene(scenePath);
  
  RayTracer rayTracer(scene);
  uint8_t *frameBuffer = rayTracer.render(width, height);

  RayFrameBuffer fb(frameBuffer, width, height);
  fb.write(outputPath);
  
  if (scene != NULL) {
    deleteScene(scene);
  }
  
  return 0;
}
