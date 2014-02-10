#include "CppUTest/CommandLineTestRunner.h"
#include "ColorTestHelper.h"
#include "ShadowTracer.h"
#include <vector>
#include "Scene.h"
#include "Matrix.h"
#include "RTSphere.h"
#include "RTMaterial.h"
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

TEST(ShadowTracer, shouldTracePerLightSource) {

  Matrix point(0,0,0);
  Light light(Matrix(10, 0, 0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  RTSphere sphere(Matrix(5, 0, 0), 2);
  scene->add(&sphere);
  
  RTColor f = stracer->shadowFactor(point, &light);

  RTColor expected(0,0,0);
  COLOR_EQUALS(expected, f);

}

TEST(ShadowTracer, shouldTraceThroughTransparantObjects) {

  Matrix point(0,0,0);
  Light light(Matrix(10, 0, 0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  RTSphere sphere(Matrix(5, 0, 0), 2);
  scene->add(&sphere);
  RTMaterial material;
  material.setKTransparency(0.5);
  sphere.addMaterial(material);
  
  RTColor f = stracer->shadowFactor(point, &light);

  RTColor expected(0.5,0.5,0.5);
  COLOR_EQUALS(expected, f);
  
}
