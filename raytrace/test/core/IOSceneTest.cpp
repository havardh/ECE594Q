#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
#include "IntersectionShaderMock.h"
#include "IOScene.h"

using testing::_;

TEST_GROUP(IOScene) {
	void setup() {}
	void teardown() {}
};

TEST(IOScene, shouldConstruct) {

  Light light(Vector(0,0,0), Vector(0,0,0), RTColor::WHITE, 0, 0);
  RTSphere sphere(Vector(0,0,0), 0);
 
  IOScene scene;
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

TEST(IOScene, shouldRetreiveTheClosestIntersect) {
  
	IOScene scene;
  RTSphere s1(Vector(0,0,0), 1);
  scene.add(&s1);
  RTSphere s2(Vector(10,0,0), 1);
  scene.add(&s2);
  RTSphere s3(Vector(-10,0,0), 1);
  scene.add(&s3);
  scene.updateTree();
  Ray ray(Vector(20,0,0), Vector(-1,0,0));

  IntersectionPtr intersection = scene.intersect(ray);
  CHECK(intersection != nullptr);
  RTShape *shape = intersection->getShape();
  
  Vector origin = ((RTSphere*)shape)->getOrigin();

  VECTOR_EQUAL(10, 0, 0, origin);
  
}

TEST(IOScene, shouldSupportDirectionalLightSources) {
  
  IOScene scene;
  
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

TEST(IOScene, shouldReturnAllIntersections) {

  IOScene scene;
  RTSphere s1(Vector(0,0,0), 1);
  scene.add(&s1);
  RTSphere s2(Vector(10,0,0), 1);
  scene.add(&s2);
  RTSphere s3(Vector(-10,0,0), 1);
  scene.add(&s3);

  Ray ray(Vector(20,0,0), Vector(-1,0,0));

  std::vector<IntersectionPtr> intersections = scene.intersections(ray);
  CHECK(intersections.size() == 3);

}

static Ray ray(Vector(0,0,0), Vector(0,0,1));
TEST_GROUP(IOSceneIntersectionShader) {
  void setup() {
  }
};

TEST(IOSceneIntersectionShader, everythingIsVisibleWhenNotShader) {
  RTSphere s(Vector(0,0,10), 1);
  IOScene scene;
  scene.add(&s);

  CHECK( scene.intersections(ray).size() == 1 );
}

TEST(IOSceneIntersectionShader, shouldReportFalseIfShaderSaysNo) {
  RTSphere s(Vector(0,0,10), 1);
  IOScene scene;
  scene.add(&s);
  NiceMock<IntersectionShaderMock> shaderMock;
  s.setIntersectionShader(&shaderMock);

  ON_CALL(shaderMock, shade(_,_,_)).WillByDefault(Return(false));

  CHECK( scene.intersections(ray).size() == 0 );
  
}

TEST(IOSceneIntersectionShader, shouldReportIntersectIfShaderSaysYes) {

  RTSphere s(Vector(0,0,10), 1);
  IOScene scene;
  scene.add(&s);
  NiceMock<IntersectionShaderMock> shaderMock;
  s.setIntersectionShader(&shaderMock);

  ON_CALL(shaderMock, shade(_,_,_)).WillByDefault(Return(true));
  CHECK( scene.intersections(ray).size() == 1 );
  
}

IGNORE_TEST(IOSceneIntersectionShader, shouldPassUVToShader) {

  RTSphere s(Vector(0,0,10), 1);
  IOScene scene;
  scene.add(&s);
  NiceMock<IntersectionShaderMock> shaderMock;
  s.setIntersectionShader(&shaderMock);

  EXPECT_CALL(shaderMock, shade(0.25, 0.5, _));
  scene.intersections(ray);
}
