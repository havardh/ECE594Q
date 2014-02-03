#include "CppUTest/CommandLineTestRunner.h"
#include "StrUtil.h"

TEST_GROUP(StrUtil) {
	void setup() {}
	void teardown() {}
};

TEST(StrUtil, shouldConstructStrUtil) {

  int width;
  int height;
  
  char param[10] = "101:120";
  
  splitWidthHeightParam(param, width, height);
  
  CHECK_EQUAL(101, width);
  CHECK_EQUAL(120, height);

}
