#include "CppUTest/CommandLineTestRunner.h"
#include "RTSphere.h"

TEST_GROUP(RTSphere) {
	void setup() {}
	void teardown() {}
};

#define check_ray(sphere, origin, direction, expected) \
  { Ray ray(origin, direction);                         \
    CHECK_EQUAL(expected, sphere.intersect(ray)); }
 

#define check_intersects(sphere, origin, direction) \
  check_ray(sphere, origin, direction, true);


#define check_not_intersects(sphere, origin, direction) \
  check_ray(sphere, origin, direction, false);


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
