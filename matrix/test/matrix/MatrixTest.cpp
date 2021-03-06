#include "CppUTest/CommandLineTestRunner.h"
#include "Matrix.h"
#include "MatrixTestHelper.h"
#include "Vector.h"

TEST_GROUP(Matrix) {
  void setup() {}
  void teardown() {}
};

TEST(Matrix, shouldContainDeepCopyConstructor) {

  Matrix m1(1);
  m1.set(0,0, 5.0);
  Matrix m2(m1);
  m1.set(0,0, 6.0);

  DOUBLES_EQUAL(5.0, m2.get(0), 0.0001);

}

TEST(Matrix, shouldHaveAVectorContructor) {
  
  float v[3] = { 1,2,3 };
	Matrix m(v);
  
  CHECK_EQUAL(3, m.getM());
  CHECK_EQUAL(1, m.getN());

  DOUBLES_EQUAL(1, m.get(0), 0.0001);
  DOUBLES_EQUAL(2, m.get(1), 0.0001);
  DOUBLES_EQUAL(3, m.get(2), 0.0001);  
}

TEST(Matrix, shouldProvideVectorGet) {
  
	Matrix m(1.0, 2.0, 4.0, 3.0);

  DOUBLES_EQUAL(1.0, m.get(0), 0.0001);
  DOUBLES_EQUAL(2.0, m.get(1), 0.0001);
  DOUBLES_EQUAL(4.0, m.get(2), 0.0001);
  DOUBLES_EQUAL(3.0, m.get(3), 0.0001);
  
}


TEST(Matrix, shouldHaveFourComponentVectorConstructor) {

  Matrix m(1, 2, 3, 4);
  
  DOUBLES_EQUAL(1.0, m.get(0), 0.0001);
  DOUBLES_EQUAL(2.0, m.get(1), 0.0001);
  DOUBLES_EQUAL(3.0, m.get(2), 0.0001);
  DOUBLES_EQUAL(4.0, m.get(3), 0.0001);
}

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

TEST(Matrix, shouldSetAndGetValuesOfRowVector) {
  
	Matrix m(1,2,3,4);

  m.set(3, 10);
  DOUBLES_EQUAL(10, m.get(3), 0.0001);
  
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

TEST(Matrix, multiplyDimensions) {

  Matrix m1(3,1);
  Matrix m2(1,2);
  Matrix m3 = m1 * m2;
  
  CHECK_EQUAL(3, m3.getM());
  CHECK_EQUAL(2, m3.getN());

}

TEST(Matrix, scale) {

  Matrix m1(4, 1);
  float v1[] = { 1, 2, 2, 1 };
  m1.setAll(v1);

  Matrix m2(3, 1);
  float v2[] = { 2, 2, 2 };
  m2.setAll(v2);

  m1.scale(m2);

  float expected[] = {
    2, 4, 4, 1
  };

  MATRIX_EQUALS(expected, m1, 0.0001);

}

TEST(Matrix, homogenize) {
  
  Matrix m1(4,1);
  float values[] = { 6, 4, 2, 2 };
  m1.setAll(values);

  m1.homogenize();

  float expected[] = {
    3, 2, 1, 1
  };

  MATRIX_EQUALS(expected, m1, 0.0001);

}

TEST(Matrix, translate) {
  
	Matrix m1(4,1);
  float v1[] = { 1, 2, 2, 1 };
  m1.setAll(v1);

  Matrix m2(3,1);
  float v2[] = { 5, 4, 1 };
  m2.setAll(v2);

  m1.translate(m2).homogenize();

  float expected[] = {
    6, 6, 3, 1
  };

  MATRIX_EQUALS(expected, m1, 0.0001);
  
}


#define rotateAndAssert(AXIS, VAR, EXP)            \
  m1.rotate(AXIS, (float)M_PI/2).homogenize();     \
  float VAR[] = EXP;                               \
  MATRIX_EQUALS(VAR, m1, 0.0001);                


TEST(Matrix, rotate) {
  
	Matrix m1(4,1);
  float v1[] = { 1, 1, 0, 1 };
  m1.setAll(v1);

  // Rotate on Z by 90
  m1.rotate(Z, (float)M_PI/2).homogenize();
  float e1[] = { -1, 1, 0, 1 };
  MATRIX_EQUALS(e1, m1, 0.0001);

  m1.rotate(Z, (float)M_PI/2).homogenize();
  float e2[] = { -1, -1, 0, 1 };
  MATRIX_EQUALS(e2, m1, 0.0001);

  m1.rotate(Z, (float)M_PI/2).homogenize();
  float e3[] = { 1, -1, 0, 1 };
  MATRIX_EQUALS(e3, m1, 0.0001);

  m1.rotate(Z, (float)M_PI/2).homogenize();
  float e4[] = { 1, 1, 0, 1 };
  MATRIX_EQUALS(e4, m1, 0.0001);

  // Rotate on X by 90
  m1.rotate(X, (float)M_PI/2).homogenize();
  float e5[] = { 1, 0, 1, 1 };
  MATRIX_EQUALS(e5, m1, 0.0001);

  m1.rotate(X, (float)M_PI/2).homogenize();
  float e6[] = { 1, -1, 0, 1 };
  MATRIX_EQUALS(e6, m1, 0.0001);
  
  m1.rotate(X, (float)M_PI/2).homogenize();
  float e7[] = { 1, 0, -1, 1 };
  MATRIX_EQUALS(e7, m1, 0.0001);
  
  m1.rotate(X, (float)M_PI/2).homogenize();
  float e8[] = { 1, 1, 0, 1 };
  MATRIX_EQUALS(e8, m1, 0.0001);
  
}

TEST(Matrix, shouldDoDotProduct) {
  
  Matrix m1(4,1);
  float v1[] = { 1, 2, 3, 4 };
  m1.setAll(v1);

  Matrix m2(4,1);
  float v2[] = { 1, 2, 3, 4 };
  m2.setAll(v2);

  float actual = m1.dot(m2);
  
  DOUBLES_EQUAL(1*1 + 2*2 + 3*3 + 4*4, actual, 0.0001);
  
}

TEST(Matrix, shouldProjectAPointOntoASpace) {
  
	Matrix p(4,1);
  float v[] = { 5, 2, 20, 1 };
  p.setAll(v);

  Matrix projectionMatrix = MatrixFactory::createPerspectiveProjection((float)M_PI/4.0f, 4.0f/3.0f, 0.1f, 40);
  p.projectOnto(projectionMatrix);

  float expected[] = {
    12, 6.6f, 19.9f, 20
  };

  MATRIX_EQUALS(expected, p, 0.1);
  
}

TEST(Matrix, shouldCompare) {
  
	Matrix m1(1,1,1);
  Matrix m2(1,1,1);
  Matrix m3(2,1,1);
  Matrix m4(1,2,1);
  Matrix m5(1,1,2);

  CHECK(m1 == m1);
  CHECK(m1 == m2);
  CHECK(m2 == m1);
  CHECK(!(m1 == m3));
  CHECK(!(m1 == m4));
  CHECK(!(m5 == m1));
  CHECK(m5 != m1);

  float v6[] = { 1, 1, 1, 1 };
  Matrix m6(2,2);
  m6.setAll(v6);
  float v7[] = { 1, 1, 1, 1 };
  Matrix m7(2,2);
  m7.setAll(v7);
  float v8[] = { 1, 1, 1, 2 };
  Matrix m8(2,2);
  m8.setAll(v8);

  CHECK(m7 == m6);
  CHECK(!(m8 == m6));
  CHECK(m6 != m8);

  CHECK(m1 != m6);
  CHECK(m6 != m1);

  
}

TEST(Matrix, crossProduct) {

  Matrix m1(1, 2, 3);
  Matrix m2(2, 2, 2);
  
  Matrix m3 = m1.crossProduct(m2);

  float expected[] = { -2, 4, -2 };

  MATRIX_EQUALS(expected, m3, 0.0001);

}

TEST(Matrix, crossProductShouldFollowRightHandRule) {

  Matrix m1(-1, 0, 0);
  Matrix m2(0, 0, 1);

  Matrix m3 = m1.crossProduct(m2);

  float expected[] = { 0, 1, 0 };

  MATRIX_EQUALS(expected, m3, 0.0001);

}

TEST(Matrix, shouldCalculateLength) {
  
	Matrix m(2,2,2);
  DOUBLES_EQUAL(3.464101615f, m.length(), 0.0001);
  
}

TEST(Matrix, shouldNormalize) {
  
	Matrix m(1, 2, 3);

  m.normalize();

  float L = 3.741657387f;

  DOUBLES_EQUAL(1.0/L, m.get(0), 0.0001);
  DOUBLES_EQUAL(2.0/L, m.get(1), 0.0001);
  DOUBLES_EQUAL(3.0/L, m.get(2), 0.0001);
  
}

TEST(Matrix, shouldMultiplyByConstant) {
  
	Matrix m(1, 2, 2);

  Matrix r = m * 2;

  DOUBLES_EQUAL(2, r.get(0), 0.0001);
  
}

TEST(Matrix, shouldSubtractTwoMatrices) {
  
	Matrix m1(2, 2, 3);
  Matrix m2(1, 1, 1);

  Matrix r = m1 - m2;

  DOUBLES_EQUAL(1, r.get(0), 0.0001);
  DOUBLES_EQUAL(1, r.get(1), 0.0001);
  DOUBLES_EQUAL(2, r.get(2), 0.0001);
  
}

TEST(Matrix, shouldProvideAbsFunction) {

  Matrix m1(1, -2, -4);
  Matrix m2 = m1.abs();

  DOUBLES_EQUAL(1, m2.get(0), 0.0001);
  DOUBLES_EQUAL(2, m2.get(1), 0.0001);
  DOUBLES_EQUAL(4, m2.get(2), 0.0001);

}

TEST(Matrix, shouldProvideDivide) {
  
	Matrix m1(1, 2, 3);
  Matrix m2(2, 2, 3);
  Matrix m3 = m1 / m2;
  
  DOUBLES_EQUAL(0.5f, m3.get(0), 0.0001);
  DOUBLES_EQUAL(1, m3.get(1), 0.0001);
  DOUBLES_EQUAL(1, m3.get(2), 0.0001);
  
}

TEST(Matrix, shouldProvideUnaryMinus) {

  Matrix m(1,0,-3);

  Matrix actual = -m;

  VECTOR_EQUAL(-1, 0, 3, actual);
  
}

TEST(Matrix, shouldProvideHadamardProduct) {
  
	Matrix m1(1, 2, 3);

  Matrix r = m1.hadamardProduct(m1);

  VECTOR_EQUAL(1, 4, 9, r);
  
}

TEST(Matrix, normalizeShouldHandleNullLength) {

  Matrix m1(0,0,0);
  m1.normalize();

  VECTOR_EQUAL(0,0,0, m1);
  

}

TEST(Matrix, shouldBeMultipliableWithVector) {

  Matrix m(4,4);
  float vals[] = {
    1,1,1,1,
    2,2,2,2,
    3,3,3,3,
    4,4,4,4
  };
  m.setAll(vals);

  Vector v( 1, 2, 3 );
  Vector r = m * v;

  float l = 4+8+12;
  VECTOR_EQUAL( (1+2+3)/l, (2+4+6)/l, (3+6+9)/l, r ); 

}
