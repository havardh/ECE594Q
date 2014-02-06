#include "CppUTest/CommandLineTestRunner.h"
#include "ShapeTestHelper.h"
#include "RTTriangle.h"

TEST_GROUP(RTTriangle) {
	void setup() {}
	void teardown() {}
};

TEST(RTTriangle, shouldCheckForIntersection) {
  
  RTTriangle triangle(Matrix(1,1,20), Matrix(2,1,40), Matrix(2,2,10));

  CHECK(triangle.intersect(Ray(Matrix(1,1,0), Matrix(0,0,1))) != nullptr);
  CHECK(triangle.intersect(Ray(Matrix(0,1,0), Matrix(0,0,1))) == nullptr);

}

TEST(RTTriangle, shouldReturnIntersectionPoint) {

  RTTriangle t(Matrix(-2,-2,10), Matrix(2,0,10), Matrix(-2,2,10));
  CHECK_INTERSECTS_AT(t, Ray(Matrix(0,0,0), Matrix(0,0,1)), 0,0,10);

}

TEST(RTTriangle, shouldReturnIntersectionPointOnARotatedTriangle) {

  RTTriangle t(Matrix(-2,-2,20), Matrix(2,0,20), Matrix(-2,2,10));
  CHECK_INTERSECTS_AT(t, Ray(Matrix(0,0,0), Matrix(0,0,1)), 0,0,17.5f);

}

TEST(RTTriangle, shouldReturnSurfaceNormalInDirectionOfTheRay) {

  RTTriangle t(Matrix(-2,-2,10), Matrix(2,0,10), Matrix(-2,2,10));
  CHECK_NORMAL_AT(t, Matrix(0,0,10), Matrix(0,0,0), 0,0,-1);

}



TEST(RTTriangle, shouldHandlePointsOnEitherSideOfTheTriangle) {

  RTTriangle t(Matrix(-2,-2,10), Matrix(2,0,10), Matrix(-2,2,10));
  CHECK_NORMAL_AT(t, Matrix(0,0,10), Matrix(0,0,20), 0,0,1);

}
