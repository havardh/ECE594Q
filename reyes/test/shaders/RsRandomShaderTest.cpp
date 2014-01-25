#include "CppUTest/CommandLineTestRunner.h"
#include "RsRandomShader.h"
#include "ShapeMock.h"
#include <stdio.h>

TEST_GROUP(RsRandomShader) {
  void setup() {}
  void teardown() {}
};


int myrand(void) {
  return 257;
}

TEST(RsRandomShader, shouldRandomizeColor) {

  float v[] = { 1,1,1,1 };
  ShapeMock shape(v, 1,1);
  shape.setColor(0,0,0);
 
  setRsRandomShaderRandFunction(&myrand);
  shape.shade(&RsRandomShader);

  Color c = shape.getMeshPoint(0,0).color;

  CHECK_EQUAL( 1, c.red );
  CHECK_EQUAL( 1, c.green );
  CHECK_EQUAL( 1, c.blue );
  
}
