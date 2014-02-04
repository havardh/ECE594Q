#include "CppUTest/CommandLineTestRunner.h"
#include "RayFactory.h"
#include <vector>
#include "Ray.h"

static Camera *camera;

TEST_GROUP(RayFactory) {
	void setup() {
    camera = new Camera(
    Matrix(0,0,0),
    Matrix(0,0,1),
    0,
    Matrix(0,1,0),
    (float)(M_PI/2)
  );
  }
	void teardown() {
    delete camera;
  }
};

TEST(RayFactory, shouldProduceRaysForCameraAnOnePixel) {
 
 
  RayFactory factory(*camera, 1, 1);

  std::vector<Ray> rays = factory.createRays();

  CHECK_EQUAL(1, rays.size());

  Matrix o = rays[0].getOrigin();
  DOUBLES_EQUAL(0, o.get(0), 0.0001);
  DOUBLES_EQUAL(0, o.get(1), 0.0001);
  DOUBLES_EQUAL(0, o.get(2), 0.0001);

  Matrix d = rays[0].getDirection();
  DOUBLES_EQUAL(0, d.get(0), 0.0001);
  DOUBLES_EQUAL(0, d.get(1), 0.0001);
  DOUBLES_EQUAL(1, d.get(2), 0.0001);

}

TEST(RayFactory, shouldProduceRaysForFourPixels) {
  
	RayFactory factory(*camera, 2, 2);

  std::vector<Ray> rays = factory.createRays();

  const int N = 4;
  CHECK_EQUAL(N, rays.size());
  for (int i=0; i<N; i++) {
    Matrix o = rays[(size_t)i].getOrigin();
    DOUBLES_EQUAL(0, o.get(0), 0.0001);
    DOUBLES_EQUAL(0, o.get(1), 0.0001);
    DOUBLES_EQUAL(0, o.get(2), 0.0001);
  }

  for (size_t i=0; i<N; i++) {
    Matrix d = rays[i].getDirection();
  }
  
}
