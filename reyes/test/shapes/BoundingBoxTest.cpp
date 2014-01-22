#include "CppUTest/CommandLineTestRunner.h"
#include "BoundingBox.h"

TEST_GROUP(BoundingBox) {
  void setup() {}
  void teardown() {}
};

TEST(BoundingBox, shouldProjectOntoScreen) {
  
	BoundingBox box(0.25f, 0.20f, 0.1f, 0.1f);
  box.projectToScreen(100, 50);

  DOUBLES_EQUAL(75, box.getX(), 0.0001);
  DOUBLES_EQUAL(35, box.getY(), 0.0001);
  DOUBLES_EQUAL(10, box.getDX(), 0.0001);
  DOUBLES_EQUAL(5, box.getDY(), 0.0001);
  
}

