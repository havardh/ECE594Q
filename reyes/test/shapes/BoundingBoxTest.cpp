#include "CppUTest/CommandLineTestRunner.h"
#include "BoundingBox.h"

TEST_GROUP(BoundingBox) {
  void setup() {}
  void teardown() {}
};

TEST(BoundingBox, shouldProjectOntoScreen) {
  
	BoundingBox box(0.25f, 0.20f, 0.1f, 0.1f);
  box.projectToScreen(100, 50);

  DOUBLES_EQUAL(62.5, box.getX(), 0.0001);
  DOUBLES_EQUAL(30, box.getY(), 0.0001);
  DOUBLES_EQUAL(10, box.getDX(), 0.0001);
  DOUBLES_EQUAL(5, box.getDY(), 0.0001);
  
}

TEST(BoundingBox, shouldProjectOntoScreenNegative) {

  BoundingBox box(-1, -1, 0, 0);
  box.projectToScreen(100, 100); 

  DOUBLES_EQUAL(0, box.getX(), 0.0001);
  DOUBLES_EQUAL(0, box.getY(), 0.0001);

}

TEST(BoundingBox, shouldProjectUpperCorner) {

  BoundingBox box(1,1,0,0);
  box.projectToScreen(10, 10);
  
  DOUBLES_EQUAL(10, box.getX(), 0.0001);
  DOUBLES_EQUAL(10, box.getY(), 0.0001);

}
