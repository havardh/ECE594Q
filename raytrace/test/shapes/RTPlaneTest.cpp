#include "CppUTest/CommandLineTestRunner.h"
#include "RTPlane.h"
#include "Ray.h"

TEST_GROUP(RTPlane) {
	void setup() {}
	void teardown() {}
};

TEST(RTPlane, shouldReportLeftOnPerpendicularRayToTheLeft) {
  
  RTPlane plane;
  plane.addTriangle(RTTriangle(Vector(5,0,0), Vector(5,5,0), Vector(5,5,5))); 
  plane.addTriangle(RTTriangle(Vector(5,0,0), Vector(5,0,5), Vector(5,5,5)));
  Ray ray(Vector(2, 3, -4), Vector(0,0,1));

  CHECK( plane.isToLeftOf(ray,0) );

}

TEST(RTPlane, shouldReportRightOnPerpendicularRayToTheRight) {
  
  RTPlane plane;
  plane.addTriangle(RTTriangle(Vector(5,0,0), Vector(5,5,0), Vector(5,5,5)));
  plane.addTriangle(RTTriangle(Vector(5,0,0), Vector(5,0,5), Vector(5,5,5)));
  Ray ray(Vector(6, 3, -4), Vector(0,0,1));

  CHECK( !plane.isToLeftOf(ray,0) );

}

TEST(RTPlane, shouldReportLeftOnPerpendicularRayToTheLeftOnYAxis) {
  
  RTPlane plane;
  plane.addTriangle(RTTriangle(Vector(0,5,0), Vector(0,5,5), Vector(5,5,5)));
  plane.addTriangle(RTTriangle(Vector(0,5,0), Vector(5,5,0), Vector(5,5,5)));
  Ray ray(Vector(3, 3, -4), Vector(0,0,1));

  CHECK( plane.isToLeftOf(ray,1) );

}

TEST(RTPlane, shouldReportRightOnPerpendicularRayToTheRightOnYAxis) {
  
  RTPlane plane;
  plane.addTriangle(RTTriangle(Vector(0,5,0), Vector(0,5,5), Vector(5,5,5)));
  plane.addTriangle(RTTriangle(Vector(0,5,0), Vector(5,5,0), Vector(5,5,5)));
  Ray ray(Vector(3, 7, -4), Vector(0,0,1));

  CHECK( !plane.isToLeftOf(ray,1) );

}

TEST(RTPlane, shouldReportRightOnPerpendicularRayToTheRightOnZAxis) {
  
  RTPlane plane;
  plane.addTriangle(RTTriangle(Vector(0,0,5), Vector(0,5,5), Vector(5,5,5)));
  plane.addTriangle(RTTriangle(Vector(0,0,5), Vector(5,0,5), Vector(5,5,5)));
  Ray ray(Vector(3, 2, 3), Vector(1,0,0));

  CHECK( plane.isToLeftOf(ray,2) );

}
