#include "CppUTest/CommandLineTestRunner.h"
#include "ColorShaderIdentity.h"

#include "RTMaterial.h"

TEST_GROUP(ColorShaderIdentity) {
	void setup() {}
	void teardown() {}
};

TEST(ColorShaderIdentity, shouldReturnTheSameMaterialBack) {
 
  ColorShaderIdentity s;
  RTMaterial m;
  m.setKTransparency(1.0);
  m.setShininess(1.0);
  CHECK( s.shade(0,0, m) == m );
 
}
