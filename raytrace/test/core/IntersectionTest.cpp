#include "CppUTest/CommandLineTestRunner.h"
#include "RTSphere.h"
#include "Intersection.h"

TEST_GROUP(Intersection) {
	void setup() {}
	void teardown() {}
};

TEST(Intersection, comparingShouldReturnTheClosestIntersection) {
 
  RTSphere s1(Vector(10, 0, 0), 2);
  Intersection i1(&s1, Ray(Vector(0,0,0), Vector(1,0,0)), Vector(8,0,0));

  RTSphere s2(Vector(14, 0, 0), 2);
  Intersection i2(&s2, Ray(Vector(0,0,0), Vector(1,0,0)), Vector(12,0,0));
  
  CHECK( i1 < i2 );
 
}
