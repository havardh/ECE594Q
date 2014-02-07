#include "CppUTest/CommandLineTestRunner.h"
#include "ShadowTracer.h"
#include <vector>
#include "Scene.h"
#include "Matrix.h"
#include "RTSphere.h"
#include "Light.h"

static Scene *scene;
static Light *light;
static ShadowTracer *stracer;

TEST_GROUP(ShadowTracer) {
	void setup() {
    scene = new Scene();
    light = new Light(Matrix(0,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
    scene->add(*light);  
    stracer = new ShadowTracer(scene);
  }
	void teardown() {
    delete scene;
    delete light;
    delete stracer;
  }
};

TEST(ShadowTracer, shouldNotReportOcclusionWhenNoObsticals) {
  
  Matrix point(10, 0, 0);
  
  CHECK(!stracer->hasOcclusion(light->getPosition(), &point));

}

TEST(ShadowTracer, shouldFindObjectOccluding) {
  
  Matrix point(10, 0, 0);
	RTSphere obstical(Matrix(4, 0, 0), 3);
  scene->add(&obstical);
  
  CHECK(stracer->hasOcclusion(light->getPosition(), &point));
}

TEST(ShadowTracer, shouldHandlePointOnSphere) {

  RTSphere sphere(Matrix(4, 0, 0), 1);
  scene->add(&sphere);
  Matrix point(3, 0, 0);
  CHECK(!stracer->hasOcclusion(light->getPosition(), &point));

}

TEST(ShadowTracer, shouldHandlePointOnTriangle) {

  RTTriangle triangle(Matrix(2,2,10), Matrix(2,-2,10), Matrix(-2,-2,10));
  scene->add(&triangle);
  Matrix point(0,0,10);
  CHECK(!stracer->hasOcclusion(light->getPosition(), &point));

}
