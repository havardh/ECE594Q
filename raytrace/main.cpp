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

#define USE_PTHREAD

void printLightStats(void);

void test() {
  Texture texture("./texture/environment/EnvironmentMaps/uffizi_latlong.exr");


  int w = 768;
  int h = 1024;
  
  RayFrameBuffer buffer(w,h);

  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      RTColor c = texture.get(i / (float)h, j / (float)w);
      buffer.set(i, j, 0, c.getRGBRed()); 
      buffer.set(i, j, 1, c.getRGBGreen());
      buffer.set(i, j, 2, c.getRGBBlue());
    }
  }
  buffer.write("test.png");
}

int main(int argc, char *argv[]) {

  //test(); return 0;
  settings.parse(argc, argv);
  settings.print();

  Timer t;
  StopWatch sw;
  sw.setTimer(&t);

  sw.start("Begining");

  Scene scene;
  SceneIO* sceneIO = readScene(settings.input());
  sw.lap("Scene read");
  scene.setScene(sceneIO);
  sw.lap("Datastructure built");
  RayFrameBuffer fb(settings.width(), settings.height());
  printf("..\n");

#ifdef USE_PTHREAD
  ThreadedRayTracer rayTracer(&scene, &fb);
#else
  RayTracer rayTracer(&scene, &fb);
#endif
  //rayTracer.setEnvironmentMap(new EnvironmentMap("./texture/earth.jpg"));
  //rayTracer.setEnvironmentMap(new EnvironmentMap("./texture/uffizi_cross.png"));
  rayTracer.setAntiAliasingResolution(1,1);

  rayTracer.render();
  sw.lap("Scene Rendered");
  printf("wtf\n");

  fb.write(settings.output());
  sw.stop();

  sw.print();
  
  if (sceneIO != NULL) {
    deleteScene(sceneIO);
  }
  printLightStats();
  return 0;
}
