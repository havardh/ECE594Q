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

#define CHECK_NOT_OCCLUSION(lpos, point) CHECK(!stracer->hasOcclusion(lpos, point)); 
#define CHECK_OCCLUSION(lpos, point) CHECK(stracer->hasOcclusion(lpos, point)); 

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
  
  CHECK_NOT_OCCLUSION(light->getPosition(), &point);

}

TEST(ShadowTracer, shouldFindObjectOccluding) {
  
  Matrix point(10, 0, 0);
	RTSphere obstical(Matrix(4, 0, 0), 3);
  scene->add(&obstical);
  
  CHECK_OCCLUSION(light->getPosition(), &point);
}

TEST(ShadowTracer, shouldHandlePointOnSphere) {

  RTSphere sphere(Matrix(4, 0, 0), 1);
  scene->add(&sphere);
  Matrix point(3, 0, 0);
  CHECK_NOT_OCCLUSION(light->getPosition(), &point);

}

TEST(ShadowTracer, shouldHandlePointOnTriangle) {

  RTTriangle triangle(Matrix(2,2,10), Matrix(2,-2,10), Matrix(-2,-2,10));
  scene->add(&triangle);
  Matrix point(0,0,10);
  CHECK_NOT_OCCLUSION(light->getPosition(), &point);

}

TEST(ShadowTracer, shouldRetreiveAllLightSources) {
  
  Light localLight(Matrix(0,1,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  scene->add(localLight);
  Matrix m(10, 0, 0);
  std::vector<const Light*> sources = stracer->getLightSources(&m);
  
  CHECK(sources.size() == 2);
  CHECK(light->getPosition() == sources[0]->getPosition());
  CHECK(localLight.getPosition() == sources[1]->getPosition());

}

TEST_GROUP(ShadowTracerBug) {
	void setup() {
    scene = new Scene();
    stracer = new ShadowTracer(scene);
  }
	void teardown() {
    delete scene;
    delete stracer;
  }
};

TEST(ShadowTracerBug, shouldHandleTriangleBehindSphere) {
  
  Light light(Matrix(-1.84647f, 0.778452f, 2.67544f), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  scene->add(light);
  
  RTSphere sphere(Matrix(-2.11537f, -0.766425f, -3.86329f), 1.33453f);
  scene->add(&sphere);

  Matrix point(-2.45382833f, -1.16149759f, -2.63432693f);

  
}
