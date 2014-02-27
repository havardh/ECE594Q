#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
#include "Snell.h"

#define ETA1 1.0
#define ETA2 1.5

TEST_GROUP(Snell) {
	void setup() {}
	void teardown() {}
};

TEST(Snell, shouldHandlePerpendicularAngle) {

  Vector N(1,0,0);
  Vector I(1,0,0);
  
  Vector D = Snell::direction(ETA1, ETA2, N, I);

  VECTOR_EQUAL(-1, 0, 0, D);
}



IGNORE_TEST(Snell, shouldHandleOrthogonalAngles) {
  
  Vector N(1,0,0);
  Vector I(0,-1,0);

  Vector D = Snell::direction(ETA1, ETA2, N, I);

  VECTOR_EQUAL(0,-1,0, D);

}

IGNORE_TEST(Snell, shouldNotAlterWhenNIsSame) {

  Vector N(1,0,0);
  Vector I(0.707107,0.707107,0);

  Vector D = Snell::direction(1,1, N, I);

  VECTOR_EQUAL(0.707107,0.707107,0, D);
  
}
