#include "CppUTest/CommandLineTestRunner.h"
#include "ColorTestHelper.h"
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
  COLOR_EQUALS( expected, (c1 * 1.2) );

}

TEST(RTColor, shouldSupportAddOperator) {
  
	RTColor c1(0.2f, 0.3f, 0.7f);
  RTColor c2(0.0f, 0.7f, 0.4f);

  RTColor expected(0.2f, 1.0f, 1.0f);
  COLOR_EQUALS( expected, (c1 + c2) );
  
}

TEST(RTColor, shouldSupportScalarAdd) {
  
	RTColor c1(0.2f, 0.3f, 0.7f);
  
  RTColor expected(0.6,0.7, 1.0);
  COLOR_EQUALS( expected, (c1 + 0.4)); 
  
}


TEST(RTColor, shouldSupportColorMultiplication) {
  
  RTColor c1(1,1,1);
  RTColor c2(0.2f, 0.3f, 2.0f);

  RTColor expected(0.2f, 0.3f, 1.0f);
  
  COLOR_EQUALS( expected, (c1 * c2) );

}
