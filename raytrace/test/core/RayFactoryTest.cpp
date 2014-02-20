#include "CppUTest/CommandLineTestRunner.h"
#include "RayFactory.h"
#include "MatrixTestHelper.h"
#include <vector>
#include "Ray.h"

static Camera *camera;

TEST_GROUP(RayFactory) {
	void setup() {
    camera = new Camera(
    Vector(0,0,0),
    Vector(0,0,-1),
    0,
    Vector(0,1,0),
    (float)(M_PI/2)
  );
  }
	void teardown() {
    delete camera;
  }
};

TEST(RayFactory, shouldProduceRaysForCameraAnOnePixel) {
 
 
  RayFactory factory(*camera, 1, 1, 1, 1);

  std::vector<Ray> rays = factory.createRays();

  CHECK_EQUAL(1, rays.size());

  Vector o = rays[0].getOrigin();
  DOUBLES_EQUAL(0, o.x(), 0.0001);
  DOUBLES_EQUAL(0, o.y(), 0.0001);
  DOUBLES_EQUAL(0, o.z(), 0.0001);

  Vector d = rays[0].getDirection();
  DOUBLES_EQUAL(0, d.x(), 0.0001);
  DOUBLES_EQUAL(0, d.y(), 0.0001);
  DOUBLES_EQUAL(-1, d.z(), 0.0001);

}

TEST(RayFactory, shouldProduceRaysForThreeByThree) {
  
	RayFactory factory(*camera, 3,3, 1, 1);

  std::vector<Ray> rays = factory.createRays();

  VECTOR_EQUAL(-0.485071, -0.485071, -0.727607, rays[0].getDirection());
  VECTOR_EQUAL(0, -0.5547, -0.83205, rays[1].getDirection());
  VECTOR_EQUAL(0.485071, -0.485071, -0.727607, rays[2].getDirection());
  
  VECTOR_EQUAL(-0.5547, 0, -0.83205, rays[3].getDirection());
  VECTOR_EQUAL(0, 0, -1, rays[4].getDirection());
  VECTOR_EQUAL(0.5547, 0, -0.83205, rays[5].getDirection());

  VECTOR_EQUAL(-0.485071 ,0.485071, -0.727607, rays[6].getDirection());
  VECTOR_EQUAL(0, 0.5547, -0.83205, rays[7].getDirection());
  VECTOR_EQUAL(0.485071, 0.485071, -0.727607, rays[8].getDirection());
  
}

TEST(RayFactory, shouldProduceRaysForThreeByThreeWhenRotated) {
  
  camera->setDirection(Vector(1,0,0));

	RayFactory factory(*camera, 3,3, 1, 1);

  std::vector<Ray> rays = factory.createRays();

  VECTOR_EQUAL(0.727607, -0.485071, -0.485071, rays[0].getDirection());
  VECTOR_EQUAL(0.83205, -0.5547, 0, rays[1].getDirection());
  VECTOR_EQUAL(0.727607, -0.485071, 0.485071, rays[2].getDirection());
  
  VECTOR_EQUAL(0.83205, 0, -0.5547, rays[3].getDirection());
  VECTOR_EQUAL(1, 0, 0, rays[4].getDirection());
  VECTOR_EQUAL(0.83205, 0, 0.5547, rays[5].getDirection());

  VECTOR_EQUAL(0.727607, 0.485071, -0.485071, rays[6].getDirection());
  VECTOR_EQUAL(0.83205, 0.5547, 0, rays[7].getDirection());
  VECTOR_EQUAL(0.727607, 0.485071, 0.485071, rays[8].getDirection());
  
}
