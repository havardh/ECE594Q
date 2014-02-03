#include "CppUTest/CommandLineTestRunner.h"
#include "Matrix.h"
#include "MatrixTestHelper.h"
#include "Camera.h"

TEST_GROUP(Camera) {
  void setup() {}
  void teardown() {}
};

TEST(Camera, shouldConstructCompleteCamera) {
  float pos[] = { 9,4,4 };
  float dir[] = { 0.5f,-0.5f,-0.6f };
  float up [] = { 0.4f, 0.8f, -0.3f };
  
  Camera c(Matrix(9,4,4), Matrix(0.5f,-0.5f,-0.6f), 0, Matrix(0.4f, 0.8f, -0.3f), (float)(M_PI/2.0));

  MATRIX_EQUALS(pos, c.getPosition(), 0.0001);
  MATRIX_EQUALS(dir, c.getDirection(), 0.0001);
  MATRIX_EQUALS(up,  c.getUp(), 0.0001);
  DOUBLES_EQUAL(M_PI/2, c.getFieldOfView(), 0.0001);
  
}
