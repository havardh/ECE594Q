#include "CppUTest/CommandLineTestRunner.h"
#include "RTMaterial.h"

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
