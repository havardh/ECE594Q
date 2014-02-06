#include "CppUTest/CommandLineTestRunner.h"
#include "Scene.h"

TEST_GROUP(Scene) {
	void setup() {}
	void teardown() {}
};

TEST(Scene, shouldConstruct) {

  Light light(Matrix(0,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  RTSphere sphere(Matrix(0,0,0), 0);
 
  Scene scene;
  scene.add(light);
  scene.add(&sphere);

  CHECK(scene.numLights() == 1);
  CHECK(scene.numShapes() == 1);

  int count=0;
  for (LightIter it = scene.lightsBegin();
       it != scene.lightsEnd();
       ++it) {
    count++;
  }
  CHECK_EQUAL(1, count);

  count=0;
  for (RTShapeIter it = scene.shapesBegin();
       it != scene.shapesEnd();
       ++it) {
    count++;
  }
  CHECK_EQUAL(1, count);
 
}
