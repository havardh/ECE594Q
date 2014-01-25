#include "CppUTest/CommandLineTestRunner.h"
#include "MyPolygon.h"
#include "MatrixTestHelper.h"
#include "BoundingBox.h"
#include "Sphere.h"
#include "Matrix.h"
#include "MatrixFactory.h"


TEST_GROUP(MyPolygon) {
  void setup() {}
  void teardown() {}

};


TEST(MyPolygon, shouldNotConstructCopies) {
    
  MyPolygon polygon;
  Matrix *m = new Matrix(-1, -1, -1, 1);
  polygon.set(0, m);
  polygon.set(1, new Matrix(1, 1, 1, 1));
  polygon.set(2, new Matrix(2, 1, 1, 1));
  polygon.set(3, new Matrix(2, -2, 0, 1));

  m->set(0,0, 5.0);
  float value = polygon.get(0)->get(0);
  DOUBLES_EQUAL(5.0, value, 0.0001);

  delete polygon.get(0);
  delete polygon.get(1);
  delete polygon.get(2);
  delete polygon.get(3);

  
}

TEST(MyPolygon, shouldSetAndGetValues) {
  
	MyPolygon polygon;
  polygon.set(0, new Matrix(0,0,0,0));
  polygon.set(1, new Matrix(1,1,1,1));
  polygon.set(2, new Matrix(2,2,2,2));
  polygon.set(3, new Matrix(3,3,3,3));

  float expected[] = {
    0,0,0,0,
    1,1,1,1,
    2,2,2,2,
    3,3,3,3
  };
  (void) expected;

  MATRIX_EQUALS(&expected[0], *polygon.get(0), 0.0001);
  MATRIX_EQUALS(&expected[4], *polygon.get(1), 0.0001);
  MATRIX_EQUALS(&expected[8], *polygon.get(2), 0.0001);
  MATRIX_EQUALS(&expected[12], *polygon.get(3), 0.0001);
  

  delete polygon.get(0);
  delete polygon.get(1);
  delete polygon.get(2);
  delete polygon.get(3);

}


TEST(MyPolygon, getBoundingBox) {
  
  MyPolygon polygon;
  polygon.set(0, new Matrix(-1,-1,1,1));
  polygon.set(1, new Matrix(-1, 2,1,1));
  polygon.set(2, new Matrix( 1, 1,1,1));
  polygon.set(3, new Matrix( 2,-3,1,1));

  BoundingBox box = polygon.getBoundingBox();

  DOUBLES_EQUAL(-1, box.getX(), 0.0001);
  DOUBLES_EQUAL(-3, box.getY(), 0.0001);
  DOUBLES_EQUAL(3, box.getDX(), 0.0001);
  DOUBLES_EQUAL(5, box.getDY(), 0.0001);

  delete polygon.get(0);
  delete polygon.get(1);
  delete polygon.get(2);
  delete polygon.get(3);

}

TEST(MyPolygon, shouldCheckForIntersects) {
  
	MyPolygon polygon;
  polygon.set(0, new Matrix(2,2,0,2));
  polygon.set(1, new Matrix(2,-2,0,2));
  polygon.set(2, new Matrix(-2,-2,0,2));
  polygon.set(3, new Matrix(-2,2,0,2));
  
  float POS_ONE = 2;
  float NEG_ONE = -2;

  CHECK(polygon.intersects(NEG_ONE, NEG_ONE));
  CHECK(polygon.intersects(NEG_ONE, POS_ONE));
  CHECK(polygon.intersects(POS_ONE, POS_ONE));
  CHECK(polygon.intersects(POS_ONE, NEG_ONE));
  CHECK(polygon.intersects(0,0));

  //CHECK(polygon.intersects(-0.3f, 0.4f));

  delete polygon.get(0);
  delete polygon.get(1);
  delete polygon.get(2);
  delete polygon.get(3);


}

TEST(MyPolygon, shouldSetAndGetColor) {

  MyPolygon p;
  Color c = { 0, 1, 2 };

  p.setColor(c);
  Color actual = p.getColor();

  CHECK_EQUAL(0, actual.red );

}

TEST(MyPolygon, shouldCreateSurfaceNormal) {


  MyPolygon polygon;
  polygon.set(0, new Matrix(0,1,0,1));
  polygon.set(1, new Matrix(1,1,0,1));
  polygon.set(2, new Matrix(1,0,0,1));
  polygon.set(3, new Matrix(0,0,0,1));

  Matrix normal = polygon.getSurfaceNormal();

  DOUBLES_EQUAL(0, normal.get(0), 0.0001);
  DOUBLES_EQUAL(0, normal.get(1), 0.0001);
  DOUBLES_EQUAL(-1, normal.get(2), 0.0001);

  delete polygon.get(0);
  delete polygon.get(1);
  delete polygon.get(2);
  delete polygon.get(3);


}
