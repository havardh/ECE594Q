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

  Matrix N(1,0,0);
  Matrix I(1,0,0);
  
  Matrix D = Snell::direction(ETA1, ETA2, N, I);

  VECTOR_EQUAL(-1, 0, 0, D);
}



TEST(Snell, shouldHandleOrthogonalAngles) {
  
  Matrix N(1,0,0);
  Matrix I(0,-1,0);

  Matrix D = Snell::direction(ETA1, ETA2, N, I);

  VECTOR_EQUAL(0,-1,0, D);

}

TEST(Snell, shouldNotAlterWhenNIsSame) {

  Matrix N(1,0,0);
  Matrix I(0.707107,0.707107,0);

  Matrix D = Snell::direction(1,1, N, I);

  VECTOR_EQUAL(0.707107,0.707107,0, D);
  
}
