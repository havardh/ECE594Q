#include "CppUTest/CommandLineTestRunner.h"
#include "IntersectionShaderVisible.h"

TEST_GROUP(IntersectionShaderVisible) {
	void setup() {}
	void teardown() {}
};

TEST(IntersectionShaderVisible, shouldReturnFalseForAllPoints) {
 
  IntersectionShaderVisible s;

  CHECK( s.shade(0,0) );
  CHECK( s.shade(1,1) );
  CHECK( s.shade(1,0) );
  CHECK( s.shade(0,1) );

  CHECK(! s.shade(-1,0) );
  CHECK(! s.shade(0,-1) );
  CHECK(! s.shade(1.1,0) );
  CHECK(! s.shade(0,1.1) );
 
}
