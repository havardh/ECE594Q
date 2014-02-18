#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GMock.h"
#include "MatrixTestHelper.h"
#include "RTPolySet.h"

TEST_GROUP(RTPolySet) {
	void setup() {}
	void teardown() {}
};

TEST(RTPolySet, shouldAddAndIntersect) {
 
  RTTriangle t1(Vector(0,0,1), Vector(1,0,1), Vector(0,1,1));
  RTTriangle t2(Vector(0,0,1), Vector(1,1,1), Vector(0,1,1));

  RTPolySet ps;

  ps.addTriangle(t1);
  ps.addTriangle(t2);
  
  {
    IntersectionPtr m = ps.intersect(Ray(Vector(0,0,0), Vector(0,0,1)));
    CHECK(m != nullptr);
  }

  {
    IntersectionPtr m = ps.intersect(Ray(Vector(1,1,0), Vector(0,0,1)));
    CHECK(m != nullptr);
  }
}


TEST(RTPolySet, shouldCalculateMidpoint) {

  RTPolySet ps;
  
  RTTriangle t1(Vector(0,0,0), Vector(1,0,0), Vector(1,0,1));
  ps.addTriangle(t1);
  RTTriangle t2(Vector(0,1,0), Vector(1,1,0), Vector(1,1,1));
  ps.addTriangle(t2);

  ps.calculateMidpoint();

  Vector m = ps.getMidpoint();
  

}

TEST(RTPolySet, boundingBoxShouldBeUnionOfTriangles) {

  RTPolySet ps;
  RTTriangle t1(Vector(0,0,0), Vector(1,0,0), Vector(1,0,1));
  ps.addTriangle(t1);
  RTTriangle t2(Vector(5,5,5), Vector(6,6,5), Vector(6,6,6));
  ps.addTriangle(t2);

  BoundingBox box = ps.getBoundingBox();

  VECTOR_EQUAL(0,0,0, box.getOrigin());
  VECTOR_EQUAL(6,6,6, box.getDelta());

}
