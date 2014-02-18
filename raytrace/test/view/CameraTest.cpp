#include "CppUTest/CommandLineTestRunner.h"
#include "Vector.h"
#include "MatrixTestHelper.h"
#include "Camera.h"

TEST_GROUP(Camera) {
  void setup() {}
  void teardown() {}
};

TEST(Camera, shouldConstructCompleteCamera) {
  
  Camera c(Vector(9,4,4), Vector(0.5f,-0.5f,-0.6f), 0, Vector(0.4f, 0.8f, -0.3f), (float)(M_PI/2.0));

  VECTOR_EQUAL(9,4,4, c.getPosition());
  VECTOR_EQUAL(0.5f,-0.5f,-0.6f, c.getDirection());
  VECTOR_EQUAL(0.4f, 0.8f, -0.3f,  c.getUp());
  DOUBLES_EQUAL(M_PI/2, c.getFieldOfView(), 0.0001);
  
}
