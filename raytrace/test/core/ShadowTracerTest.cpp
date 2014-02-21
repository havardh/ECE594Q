#include "CppUTest/CommandLineTestRunner.h"
#include "ColorTestHelper.h"
#include "ShadowTracer.h"
#include <vector>
#include "Scene.h"
#include "Vector.h"
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
    light = new Light(Vector(0,0,0), Vector(0,0,0), RTColor::WHITE, 0, 0);
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
  
  Vector point(10, 0, 0);
  
  CHECK_NOT_OCCLUSION(light->getPosition(), &point);

}

TEST(ShadowTracer, shouldFindObjectOccluding) {
  
  Vector point(10, 0, 0);
	RTSphere obstical(Vector(4, 0, 0), 3);
  scene->add(&obstical);
  scene->updateTree();
  
  CHECK_OCCLUSION(light->getPosition(), &point);
}

TEST(ShadowTracer, shouldHandlePointOnSphere) {

  RTSphere sphere(Vector(4, 0, 0), 1);
  scene->add(&sphere);
  Vector point(3, 0, 0);
  CHECK_NOT_OCCLUSION(light->getPosition(), &point);

}

TEST(ShadowTracer, shouldHandlePointOnTriangle) {

  RTTriangle triangle(Vector(2,2,10), Vector(2,-2,10), Vector(-2,-2,10));
  scene->add(&triangle);
  Vector point(0,0,10);
  CHECK_NOT_OCCLUSION(light->getPosition(), &point);

}

TEST(ShadowTracer, shouldRetreiveAllLightSources) {
  
  Light localLight(Vector(0,1,0), Vector(0,0,0), RTColor::WHITE, 0, 0);
  scene->add(localLight);
  Vector m(10, 0, 0);
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

IGNORE_TEST(ShadowTracer, shouldTracePerLightSource) {

  Vector point(0,0,0);
  Light light(Vector(10, 0, 0), Vector(0,0,0), RTColor::WHITE, 0, 0);
  RTSphere sphere(Vector(5, 0, 0), 2);
  scene->add(&sphere);
  
  RTColor f = stracer->shadowFactor(point, &light);

  RTColor expected(0,0,0);
  COLOR_EQUALS(expected, f);

}

IGNORE_TEST(ShadowTracer, shouldTraceThroughTransparantObjects) {

  Vector point(0,0,0);
  Light light(Vector(10, 0, 0), Vector(0,0,0), RTColor::WHITE, 0, 0);
  RTSphere sphere(Vector(5, 0, 0), 2);
  scene->add(&sphere);
  RTMaterial material;
  material.setKTransparency(0.5);
  sphere.addMaterial(material);
  
  RTColor f = stracer->shadowFactor(point, &light);

  RTColor expected(0.5,0.5,0.5);
  COLOR_EQUALS(expected, f);
  
}
