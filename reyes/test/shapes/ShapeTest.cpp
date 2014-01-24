#include "CppUTest/CommandLineTestRunner.h"
#include "Shape.h"

TEST_GROUP(Shape) {
  void setup() {}
  void teardown() {}
};

TEST(Shape, shouldSetGetColor) {
  
	Shape s;
  s.setColor(1, 2, 3);
  Color c = s.getColor();
  CHECK_EQUAL(1, c.red);
  CHECK_EQUAL(2, c.green);
  CHECK_EQUAL(3, c.blue);
  
}


TEST(Shape, shouldSetOpacity) {
  
	Shape s;
  s.setOpacity(0.5);
  DOUBLES_EQUAL(0.5, s.getOpacity(), 0.0001);
  
}

