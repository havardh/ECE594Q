#include "CppUTest/CommandLineTestRunner.h"
#include "Mesh.h"
#include "Sphere.h"

TEST_GROUP(Mesh) {
  void setup() {}
  void teardown() {}
};


TEST(Mesh, shouldComputeBoundingBox) {
  
	Mesh *m = new Sphere(1);

  BoundingBox box = m->getBoundingBox();

  DOUBLES_EQUAL(-1, box.x, 0.02);
  DOUBLES_EQUAL(-1, box.y, 0.02);
  DOUBLES_EQUAL(2, box.dx, 0.02);
  DOUBLES_EQUAL(2, box.dy, 0.02);

  delete m;
}
