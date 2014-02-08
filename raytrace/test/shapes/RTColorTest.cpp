#include "CppUTest/CommandLineTestRunner.h"
#include "RTColor.h"

TEST_GROUP(RTColor) {
	void setup() {}
	void teardown() {}
};

TEST(RTColor, shouldSupportEqualsOperator) {
  
  RTColor c1(0.5f, 0.5f, 0.5f);
  RTColor c2(0.5f, 0.5f, 0.5f);
  
  CHECK( c1 == c2 );
  CHECK( c1 != RTColor::WHITE );
  CHECK( c1 != RTColor::BLACK );
  
}

TEST(RTColor, shouldSupportMultiplicationOperator) {

  RTColor c1(0.2f, 0.2f, 0.2f);

  RTColor expected(0.24f, 0.24f, 0.24f);
  CHECK( (c1 * 1.2) == expected );

}
