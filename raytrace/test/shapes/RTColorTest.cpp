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

TEST(RTColor, shouldSupportAddEquals) {
  
	RTColor c1(0.1f, 0.1f, 0.9f);
  RTColor c2(0.1f, 0.1f, 0.9f);
  
  c1 += c2;

  RTColor expected(0.2, 0.2, 1);
  COLOR_EQUALS( expected, c1 );
  
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

TEST(RTColor, shouldSupportComparisonWithScalar) {
  
  RTColor c1(0.1, 0.2, 0.3);
  RTColor c2(0.1, 0.4, 0.3);
  RTColor cl(0,0,0);
  RTColor ch(1,1,1);

  CHECK( c1 < 1 );
  CHECK( !(c1 < 0) );
  CHECK( !(c1 < 0.2) );
  CHECK( !(c2 < 0.35) );
  CHECK( !(cl < 0) );
  CHECK( !(ch < 1) );
  CHECK( cl < 0.00000000001);
  CHECK( !(ch < 0.9999999999) );
  
}

IGNORE_TEST(RTColor, shouldNormalize) {

  RTColor c(0.1, 0.3, 0.5);
  //c.normalize();

}
