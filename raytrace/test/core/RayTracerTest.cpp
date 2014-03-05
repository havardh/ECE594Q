#include "CppUTest/CommandLineTestRunner.h"
#include "scene_io.h"
#include "RayTracer.h"
#include "IOScene.h"

static IOScene *scene;
static SceneIO sceneIO;
  

TEST_GROUP(RayTracer) {
	void setup() {
    sceneIO.camera = new CameraIO;
    sceneIO.camera->position[0] = -9.58772f; 
    sceneIO.camera->position[1] = 4.26363f; 
    sceneIO.camera->position[2] = 4.60779f;

    sceneIO.camera->viewDirection[0] = 0.580339f; 
    sceneIO.camera->viewDirection[1] = -0.523277f; 
    sceneIO.camera->viewDirection[2] = -0.62401f;

    sceneIO.camera->focalDistance = 12.2118f;
    
    sceneIO.camera->orthoUp[0] = 0.411139f;
    sceneIO.camera->orthoUp[1] = 0.849684f;
    sceneIO.camera->orthoUp[2] = -0.330155f;

    sceneIO.camera->verticalFOV = 0.785398f;
    
    scene = new IOScene;
    scene->setScene(&sceneIO);
  }
	void teardown() {
    delete sceneIO.camera;
    delete scene;
  }
};

TEST(RayTracer, shouldConstructRayTracer) {

  RayFrameBuffer fb(0,0);
  RayTracer r(scene, &fb);
  
}

TEST(RayTracer, shouldRender) {

  //sceneIO.camera->position[0] = 0;
  //sceneIO.camera->position[1] = 0; 
  //sceneIO.camera->position[2] = 0;
  //sceneIO.camera->viewDirection[0] = 0; 
  //sceneIO.camera->viewDirection[1] = 0; 
  //sceneIO.camera->viewDirection[2] = 1;
  //sceneIO.camera->orthoUp[0] = 0;
  //sceneIO.camera->orthoUp[1] = 1;
  //sceneIO.camera->orthoUp[2] = 0;
  //sceneIO.camera->verticalFOV = (float)(M_PI / 4.0);
  //scene->setScene(&sceneIO);
 
  RayFrameBuffer fb(4,4);
	RayTracer rayTracer(scene, &fb);
  rayTracer.render();
  
}

