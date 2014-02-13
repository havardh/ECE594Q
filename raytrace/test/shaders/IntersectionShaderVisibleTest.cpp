#include "CppUTest/CommandLineTestRunner.h"
#include "IntersectionShaderVisible.h"

TEST_GROUP(IntersectionShaderVisible) {
	void setup() {}
	void teardown() {}
};

TEST(IntersectionShaderVisible, shouldReturnFalseForAllPoints) {
 
  IntersectionShaderVisible s;
  RTMaterial m;

  CHECK( s.shade(0,0, m ));
  CHECK( s.shade(1,1, m ));
  CHECK( s.shade(1,0, m ));
  CHECK( s.shade(0,1, m ));

  CHECK(! s.shade(-1,0, m ));
  CHECK(! s.shade(0,-1, m ));
  CHECK(! s.shade(1.1,0, m ));
  CHECK(! s.shade(0,1.1, m ));
 
}
