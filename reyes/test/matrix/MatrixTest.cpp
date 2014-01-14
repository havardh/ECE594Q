#include "CppUTest/CommandLineTestRunner.h"
#include "Matrix.h"
#include "MatrixTestHelper.h"

TEST_GROUP(Matrix) {
  void setup() {}
  void teardown() {}
};

TEST(Matrix, shouldCreateSquareMatrix) {
  
	Matrix m(4);

  CHECK_EQUAL(4, m.getM());
  CHECK_EQUAL(4, m.getN());
  
}


TEST(Matrix, shouldSetAndGetValues) {
  Matrix m(4);
  
  m.set(0, 0, 1.0);
  DOUBLES_EQUAL(1.0, m.get(0, 0), 0.0001);

}

TEST(Matrix, shouldSetAll) {
  
	Matrix m(2);

  float values[] = { 2,3,5,1 };
  m.setAll(values);

  MATRIX_EQUALS(values, m, 0.0001); 
  
}


TEST(Matrix, assignment) {
  
  Matrix m1(2);
  float values[] = { 1.0, 2.0, 3.0, 4.0 };
  m1.setAll(values);
  Matrix m2(2);
  
  m2 = m1;


  MATRIX_EQUALS(values, m2, 0.0001);
}


TEST(Matrix, multiply) {

  Matrix m1(2);
  float v1[] = { 1.0, 1.0, 1.0, 1.0 };
  m1.setAll(v1);
  Matrix m2(2);
  float v2[] = { 1.0, 1.0, 1.0, 1.0 };
  m2.setAll(v2);
  float expected[] = { 2.0, 2.0, 2.0, 2.0 };

  Matrix m3 = m1 * m2;

  MATRIX_EQUALS(expected, m3, 0.0001);

}
