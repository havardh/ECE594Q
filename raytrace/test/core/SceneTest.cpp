#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
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

TEST(Scene, shouldRetreiveTheClosestIntersect) {
  
	Scene scene;
  RTSphere s1(Matrix(0,0,0), 1);
  scene.add(&s1);
  RTSphere s2(Matrix(10,0,0), 1);
  scene.add(&s2);
  RTSphere s3(Matrix(-10,0,0), 1);
  scene.add(&s3);

  Ray ray(Matrix(20,0,0), Matrix(-1,0,0));

  IntersectionPtr intersection = scene.intersect(ray);
  CHECK(intersection != nullptr);
  RTShape *shape = intersection->getShape();
  
  Matrix origin = ((RTSphere*)shape)->getOrigin();

  VECTOR_EQUAL(10, 0, 0, origin);
  
}

TEST(Scene, shouldSupportDirectionalLightSources) {
  
  Scene scene;
  
  LightIO lio[] = {{
      0,
      DIRECTIONAL_LIGHT,
      {0,0,0},
      {0,0,0},
      {0,0,0},
      0,0
    }};
  
  scene.setLights(lio);
  const Light light = *scene.lightsBegin();

  CHECK(light.getType() == DIRECTIONAL);
  
}
