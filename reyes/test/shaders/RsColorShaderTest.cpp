#include "CppUTest/CommandLineTestRunner.h"
#include "RsColorShader.h"
#include "ShapeMock.h"
#include <stdio.h>

TEST_GROUP(RsColorShader) {
  void setup() {}
  void teardown() {}
};


TEST(RsColorShader, shouldRandomizeColor) {

  float v[] = { 1,1,1,1 };
  ShapeMock shape(v, 1,1);
  shape.setColor(0,0,0);
  
  shape.shade(&RsColorShader);

  Color c = shape.getMeshPoint(0,0).color;

  CHECK( c.red != 0 );
  CHECK( c.green != 0 );
  CHECK( c.blue != 0 );
  
}
