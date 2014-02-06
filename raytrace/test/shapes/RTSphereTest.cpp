#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
#include "RTSphere.h"

TEST_GROUP(RTSphere) {
	void setup() {}
	void teardown() {}
};

#define CHECK_INTERSECTS_AT(s, ray, x, y, z)    \
  {                                             \
    MatrixPtr I = s.intersect(ray);             \
    CHECK( I != nullptr );                      \
    DOUBLES_EQUAL(x, I->get(0), 0.0001);        \
    DOUBLES_EQUAL(y, I->get(1), 0.0001);        \
    DOUBLES_EQUAL(z, I->get(2), 0.0001);        \
  }

#define CHECK_NORMAL_AT(s, point, x, y, z)  \
  {                                             \
    MatrixPtr I = s.normal(point);              \
    CHECK( I != nullptr );                      \
    DOUBLES_EQUAL(x, I->get(0), 0.0001);        \
    DOUBLES_EQUAL(y, I->get(1), 0.0001);        \
    DOUBLES_EQUAL(z, I->get(2), 0.0001);        \
  }


#define check_intersects(sphere, origin, direction) \
  { Ray ray(origin, direction);                     \
    CHECK(sphere.intersect(ray) != nullptr); }

#define check_not_intersects(sphere, origin, direction) \
  { Ray ray(origin, direction);                         \
    CHECK(sphere.intersect(ray) == nullptr); }

TEST(RTSphere, shouldCheckForIntersection) {
 
  RTSphere s(Matrix(10, 10, 10), 2);

  // A ray straight at it from the origin
  check_intersects(s, Matrix(0,0,0), Matrix(1,1,1));
  
  // A ray straight at it from x-y axis
  check_intersects(s, Matrix(10, 10, 0), Matrix(0,0,1));
  // From the axis on the top,bottom,left,right
  check_intersects(s, Matrix(8, 10, 0), Matrix(0,0,1));
  check_intersects(s, Matrix(12, 10, 0), Matrix(0,0,1));
  check_intersects(s, Matrix(10, 8, 0), Matrix(0,0,1));
  check_intersects(s, Matrix(10, 12, 0), Matrix(0,0,1));
  // From the axis on the corner
  check_not_intersects(s, Matrix(8, 12, 0), Matrix(0,0,1));
  check_not_intersects(s, Matrix(12, 12, 0), Matrix(0,0,1));
  check_not_intersects(s, Matrix(8, 8, 0), Matrix(0,0,1));
  check_not_intersects(s, Matrix(12, 8, 0), Matrix(0,0,1));

  // Diagonals missing
  check_not_intersects(s, Matrix(10, 10, 0), Matrix(1,1,1));
}

TEST(RTSphere, shouldIntersectOnClosedPointIfCommingFromTheLeft) {
  
  RTSphere s(Matrix(0,0,10), 2);
  
  CHECK_INTERSECTS_AT(s, Ray(Matrix(0,0,0), Matrix(0,0,1)), 0,0,8);
  
}

TEST(RTSphere, shouldIntersectOnTheSideOfASphere) {

  RTSphere s(Matrix(0,0,10), 2);
  
	CHECK_INTERSECTS_AT(s, Ray(Matrix(2,0,0), Matrix(0,0,1)), 2,0,10);
  
}

TEST(RTSphere, shouldIntersectOnClosedPointIfCommingFromTheRight) {
  
  RTSphere s(Matrix(0,0,10), 2);
	CHECK_INTERSECTS_AT(s, Ray(Matrix(0,0,20), Matrix(0,0,-1)), 0,0,12);
  
}

TEST(RTSphere, normalShouldAlongZAxisNegativeOnFront) {

  RTSphere s(Matrix(0,0,10), 1);
  CHECK_NORMAL_AT(s, Matrix(0,0,8), 0,0,-1);
  
}

TEST(RTSphere, normalShouldAlongZAxisPositiveOnRear) {

  RTSphere s(Matrix(0,0,10), 1);
  CHECK_NORMAL_AT(s, Matrix(0,0,12), 0,0,1);
  
}


TEST(RTSphere, normalShouldBeOnXAxisToTheRight) {

  RTSphere s(Matrix(0,0,10), 1);
  CHECK_NORMAL_AT(s, Matrix(2,0,10), 1,0,0);
  
}
