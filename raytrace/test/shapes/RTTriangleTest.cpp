#include "CppUTest/CommandLineTestRunner.h"
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
