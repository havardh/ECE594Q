#include "CppUTest/CommandLineTestRunner.h"
#include "SurfaceAreaHeuristic.h"

TEST_GROUP(SurfaceAreaHeuristic) {
	void setup() {}
	void teardown() {}
};

TEST(SurfaceAreaHeuristic, shouldSplitUpOnBest) {
  
  BoundingBox box(Vector(-2,-1,-1), Vector(4,2,2));
  vector<RTShape*> shapes;
  RTSphere sphere(Vector(1,1,1), 1);
  shapes.push_back(&sphere);

  SurfaceAreaHeuristic sah;

  float median = sah.findMedian(box, shapes, 0);

  DOUBLES_EQUAL( 0, median, 0.0001 );

}
