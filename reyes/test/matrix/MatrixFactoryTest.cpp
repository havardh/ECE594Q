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
  
	Matrix v(3,1);
  float values[] = { 1.0, 2.0, 3.0 };
  v.setAll(values);

  float expected[] = {
    1.0, 0.0, 0.0, 0.0, 
    0.0, 2.0, 0.0, 0.0, 
    0.0, 0.0, 3.0, 0.0, 
    0.0, 0.0, 0.0, 1.0 
  };

  Matrix s = MatrixFactory::createScale(v);

  CHECK_EQUAL(4, s.getM());
  CHECK_EQUAL(4, s.getN());

  MATRIX_EQUALS(expected, s, 0.0001);
  
}

TEST(MatrixFactory, shouldCreateRotationOnZWithZeroAngle) {
  
  Matrix m = MatrixFactory::createRotation(Z, 0);

  float expected[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);
  
}

TEST(MatrixFactory, shouldCreateRotationOnZWithPIAngle) {
  
	Matrix m = MatrixFactory::createRotation(Z, (float)M_PI);

  float expected[] = {
    -1, 0, 0, 0, 
    0, -1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);  
}

TEST(MatrixFactory, shouldCreateRotationOnZWithPIHalfAngle) {
  
	Matrix m = MatrixFactory::createRotation(Z, (float)M_PI/2);

  float expected[] = {
    0, -1, 0, 0, 
    1, 0, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);  
}

TEST(MatrixFactory, shouldCreateRotationOnZWith7PIHalfAngle) {
  
	Matrix m = MatrixFactory::createRotation(Z, (float)M_PI/2*7);

  float expected[] = {
    0, 1, 0, 0, 
    -1, 0, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);  
}

TEST(MatrixFactory, shouldCreateRotationOnXWithZeroAngle) {
  
  Matrix m = MatrixFactory::createRotation(X, 0);

  float expected[] = {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);
  
}

TEST(MatrixFactory, shouldCreateRotationOnXWithPIAngle) {
  
	Matrix m = MatrixFactory::createRotation(X, (float)M_PI);

  float expected[] = {
    1, 0, 0, 0, 
    0, -1, 0, 0,
    0, 0, -1, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);  
}

TEST(MatrixFactory, shouldCreateRotationOnXWithPIHalfAngle) {
  
	Matrix m = MatrixFactory::createRotation(X, (float)M_PI/2);

  float expected[] = {
    1, 0, 0, 0, 
    0, 0, -1, 0,
    0, 1, 0, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);  
}

TEST(MatrixFactory, shouldCreateRotationOnXWith7PIHalfAngle) {
  
	Matrix m = MatrixFactory::createRotation(X, (float)M_PI/2*7);

  float expected[] = {
    1, 0, 0, 0, 
    0, 0, 1, 0,
    0, -1, 0, 0,
    0, 0, 0, 1
  };
  
  MATRIX_EQUALS(expected, m, 0.0001);  
}

