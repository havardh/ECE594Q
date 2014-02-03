#include "CppUTest/CommandLineTestRunner.h"
#include "scene_io.h"
#include "RayTracer.h"

static SceneIO scene;
  

TEST_GROUP(RayTracer) {
	void setup() {
    scene.camera = new CameraIO;
    scene.camera->position[0] = -9.58772f; 
    scene.camera->position[1] = 4.26363f; 
    scene.camera->position[2] = 4.60779f;

    scene.camera->viewDirection[0] = 0.580339f; 
    scene.camera->viewDirection[1] = -0.523277f; 
    scene.camera->viewDirection[2] = -0.62401f;

    scene.camera->focalDistance = 12.2118f;
    
    scene.camera->orthoUp[0] = 0.411139f;
    scene.camera->orthoUp[1] = 0.849684f;
    scene.camera->orthoUp[2] = -0.330155f;

    scene.camera->verticalFOV = 0.785398f;

  }
	void teardown() {
    delete scene.camera;
  }
};

TEST(RayTracer, shouldConstructRayTracer) {
  
  RayTracer r(&scene);
  
}

TEST(RayTracer, shouldRender) {
  
	RayTracer rayTracer(&scene);
  uint8_t *fb = rayTracer.render(10,10);
  (void) fb;
  
}

