#include "CppUTest/CommandLineTestRunner.h"
#include "Matrix.h"
#include "MatrixFactory.h"
#include "MatrixTestHelper.h"

TEST_GROUP(MatrixFactory) {
  void setup() {}
  void teardown() {}
};

TEST(MatrixFactory, shouldCreateIdentity) {
  Matrix ident = MatrixFactory::createIdentity(2);

  DOUBLES_EQUAL(1.0, ident.get(0,0), 0.0001);
  DOUBLES_EQUAL(0.0, ident.get(0,1), 0.0001);
  DOUBLES_EQUAL(0.0, ident.get(1,0), 0.0001);
  DOUBLES_EQUAL(1.0, ident.get(1,1), 0.0001);
}

TEST(MatrixFactory, shouldCreateTranslation) {
  
	Matrix v(3,1);
  float values[] = { 1.0, 2.0, 3.0 };
  v.setAll(values);
  
  Matrix t = MatrixFactory::createTranslation(v);

  float array[] = { 
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 2.0,
    0.0, 0.0, 1.0, 3.0,
    0.0, 0.0, 0.0, 1.0
  };
  MATRIX_EQUALS(array, t, 0.0001); 
  
}

TEST(MatrixFactory, shouldCreateScale) {
  
	Matrix v(4,1);
  float values[] = { 1.0, 2.0, 3.0, 4.0 };
  v.setAll(values);

  float expected[] = {
    1.0, 0.0, 0.0, 0.0, 
    0.0, 2.0, 0.0, 0.0, 
    0.0, 0.0, 3.0, 0.0, 
    0.0, 0.0, 0.0, 4.0 
  };

  Matrix s = MatrixFactory::createScale(v);

  MATRIX_EQUALS(expected, s, 0.0001);
  
}

TEST(MatrixFactory, shouldCreateRotation) {
  
  Matrix v(4,1);
  float values[] = { 
  
}

