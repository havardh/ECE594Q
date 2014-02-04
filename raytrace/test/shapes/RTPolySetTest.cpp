#include "CppUTest/CommandLineTestRunner.h"
#include "RTPolySet.h"

TEST_GROUP(RTPolySet) {
	void setup() {}
	void teardown() {}
};

TEST(RTPolySet, shouldAddAndIntersect) {
 
  RTTriangle t1(Matrix(0,0,1), Matrix(1,0,1), Matrix(0,1,1));
  RTTriangle t2(Matrix(0,0,1), Matrix(1,1,1), Matrix(0,1,1));

  RTPolySet ps;

  ps.addTriangle(t1);
  ps.addTriangle(t2);

  CHECK(ps.intersect(Ray(Matrix(0,0,0), Matrix(0,0,1))));
  CHECK(ps.intersect(Ray(Matrix(1,1,0), Matrix(0,0,1))));
 
}
