#include "CppUTest/CommandLineTestRunner.h"
#include "RTMaterial.h"
#include "ColorTestHelper.h"

TEST_GROUP(RTMaterial) {
	void setup() {}
	void teardown() {}
};

TEST(RTMaterial, shouldProvideComparisonForEquality) {
  
  RTMaterial m1;
  RTMaterial m2;

  CHECK( m1 == m1 );
  

  m1 = m2; CHECK( m1 == m2 );
  m2.setKTransparency(1.0);
  CHECK( m1 != m2 );

  m1 = m2; CHECK( m1 == m2 );
  m2.setShininess(1.0);
  CHECK( m1 != m2 );

  m1 = m2; CHECK( m1 == m2 );
  m2.setDiffColor(RTColor(1,1,1));
  CHECK( m1 != m2 );

  m1 = m2; CHECK( m1 == m2 );
  m2.setAmbColor(RTColor(1,1,1));
  CHECK( m1 != m2 );

  m1 = m2; CHECK( m1 == m2 );
  m2.setEmissColor(RTColor(1,1,1));
  CHECK( m1 != m2 );

  m1 = m2; CHECK( m1 == m2 );
  m2.setSpecColor(RTColor(1,1,1));
  CHECK( m1 != m2 );

}

TEST(RTMaterial, shouldSupportAddition) {

  RTMaterial m1;
  m1.setKTransparency(0.1);
  m1.setShininess(0.2);
  m1.setDiffColor(RTColor(0,0.1,0.2));
  m1.setSpecColor(RTColor(0,0.1,0.2));
  m1.setAmbColor(RTColor(0,0.1,0.2));
  m1.setEmissColor(RTColor(0,0.1,0.2));

  RTMaterial m2;
  m2.setKTransparency(0.3);
  m2.setShininess(0.2);
  m2.setDiffColor(RTColor(0,0.1,0.2));
  m2.setSpecColor(RTColor(0,0.1,0.2));
  m2.setAmbColor(RTColor(0,0.1,0.2));
  m2.setEmissColor(RTColor(0,0.1,0.2));

  m1 += m2;

  DOUBLES_EQUAL( 0.4, m1.getKTransparency(), 0.00001 );
  DOUBLES_EQUAL( 0.4, m1.getShininess(), 0.00001 );
  COLOR_EQUAL(0, 51, 102, m1.getDiffColor() );
  COLOR_EQUAL(0, 51, 102, m1.getSpecColor() );
  COLOR_EQUAL(0, 51, 102, m1.getAmbColor() );
  COLOR_EQUAL(0, 51, 102, m1.getEmissColor() );
}

TEST(RTMaterial, shouldSupportMultiplication) {

  RTMaterial m1;
  m1.setKTransparency(0.1);
  m1.setShininess(0.2);
  m1.setDiffColor(RTColor(0,0.1,0.2));
  m1.setSpecColor(RTColor(0,0.1,0.2));
  m1.setAmbColor(RTColor(0,0.1,0.2));
  m1.setEmissColor(RTColor(0,0.1,0.2));

  m1 *= 0.5;

  DOUBLES_EQUAL( 0.05, m1.getKTransparency(), 0.00001 );
  DOUBLES_EQUAL( 0.1, m1.getShininess(), 0.00001 );
  COLOR_EQUAL(0, 12, 25, m1.getDiffColor() );
  COLOR_EQUAL(0, 12, 25, m1.getSpecColor() );
  COLOR_EQUAL(0, 12, 25, m1.getAmbColor() );
  COLOR_EQUAL(0, 12, 25, m1.getEmissColor() );
}
