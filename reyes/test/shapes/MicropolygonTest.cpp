#include "CppUTest/CommandLineTestRunner.h"
#include "Micropolygon.h"
#include "MatrixTestHelper.h"
#include "BoundingBox.h"
#include "Sphere.h"
#include "Matrix.h"
#include "MatrixFactory.h"


TEST_GROUP(Micropolygon) {
void setup() {}
void teardown() {}
};

static Matrix values[4] = {
  Matrix(-1, -1, -1, 1),
  Matrix(1, 1, 1, 1),
  Matrix(2, 1, 1, 1),
  Matrix(2, -2, 0, 1)
};


TEST(Micropolygon, shouldConstructCopies) {
    
  Micropolygon polygon(values);

  values[0].set(0,0, 5.0);
  float value = polygon.get(0).get(0);
  DOUBLES_EQUAL(-1.0, value, 0.0001);
  
}

TEST(Micropolygon, shouldSetAndGetValues) {
  
	Micropolygon polygon;
  polygon.set(0, Matrix(0,0,0,0));
  polygon.set(1, Matrix(1,1,1,1));
  polygon.set(2, Matrix(2,2,2,2));
  polygon.set(3, Matrix(3,3,3,3));

  float expected[] = {
    0,0,0,0,
    1,1,1,1,
    2,2,2,2,
    3,3,3,3
  };
  (void) expected;

  MATRIX_EQUALS(&expected[0], polygon.get(0), 0.0001);
  MATRIX_EQUALS(&expected[4], polygon.get(1), 0.0001);
  MATRIX_EQUALS(&expected[8], polygon.get(2), 0.0001);
  MATRIX_EQUALS(&expected[12], polygon.get(3), 0.0001);
  
}


TEST(Micropolygon, getBoundingBox) {
  
  Micropolygon polygon;
  polygon.set(0, Matrix(-1,-1,1,1));
  polygon.set(1, Matrix(-1, 2,1,1));
  polygon.set(2, Matrix( 1, 1,1,1));
  polygon.set(3, Matrix( 2,-3,1,1));

  BoundingBox box = polygon.getBoundingBox();

  DOUBLES_EQUAL(-1, box.getX(), 0.0001);
  DOUBLES_EQUAL(-3, box.getY(), 0.0001);
  DOUBLES_EQUAL(3, box.getDX(), 0.0001);
  DOUBLES_EQUAL(5, box.getDY(), 0.0001);
}

TEST(Micropolygon, shouldCheckForIntersects) {
  
	Micropolygon polygon;
  polygon.set(0, Matrix(2,2,0,2));
  polygon.set(1, Matrix(2,-2,0,2));
  polygon.set(2, Matrix(-2,-2,0,2));
  polygon.set(3, Matrix(-2,2,0,2));
  
  float POS_ONE = 2;
  float NEG_ONE = -2;

  CHECK(polygon.intersects(NEG_ONE, NEG_ONE));
  CHECK(polygon.intersects(NEG_ONE, POS_ONE));
  CHECK(polygon.intersects(POS_ONE, POS_ONE));
  CHECK(polygon.intersects(POS_ONE, NEG_ONE));
  CHECK(polygon.intersects(0,0));

  //CHECK(polygon.intersects(-0.3f, 0.4f));

}

TEST(Micropolygon, shouldSetAndGetColor) {

  Micropolygon p;
  Color c = { 0, 1, 2 };

  p.setColor(c);
  Color actual = p.getColor();

  CHECK_EQUAL(0, actual.red );

}


