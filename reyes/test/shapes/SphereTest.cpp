#include "CppUTest/CommandLineTestRunner.h"
#include "Sphere.h"

TEST_GROUP(Sphere) {
  void setup() {}
  void teardown() {}
};


TEST(Sphere, shouldCalculatePointsOnSphere) {
  
	Sphere s(1, 1, 1, 1);
  
}
