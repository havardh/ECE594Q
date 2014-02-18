#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
#include "Vector.h"

TEST_GROUP(Vector) {
	void setup() {}
	void teardown() {}
};

TEST(Vector, shouldHaveDefaultConstructor) {
 
  Vector v;
  VECTOR_EQUAL(0,0,0, v);

}

TEST(Vector, shouldHaveTreeComponentArrayConstructor) {
  float values[] { 1,2,3 };
  Vector v(values);

  VECTOR_EQUAL( 1, 2, 3, v);

  
}

TEST(Vector, shouldProvideTreeValueConstructor) {

  Vector v(5, 6, 1);

  VECTOR_EQUAL( 5, 6, 1, v );

}

TEST(Vector, shouldProvideSetAndGet) {

  Vector v;

  v.x(4); v.y(1), v.z(7);

  DOUBLES_EQUAL(v.x(), 4, 0.0001);
  DOUBLES_EQUAL(v.y(), 1, 0.0001);
  DOUBLES_EQUAL(v.z(), 7, 0.0001);

  v.set(X_AXIS,2); v.set(Y_AXIS,3), v.set(Z_AXIS,1);

  DOUBLES_EQUAL(v.get(X_AXIS), 2, 0.0001);
  DOUBLES_EQUAL(v.get(Y_AXIS), 3, 0.0001);
  DOUBLES_EQUAL(v.get(Z_AXIS), 1, 0.0001);
  
}

TEST(Vector, shouldProvideSubtractionOperator) {

  Vector v1(1,2,3);
  Vector v2(1,1,1);

  VECTOR_EQUAL( 0, 1, 2, (v1 - v2) );
  Vector v3 = v2 -= v1;
  VECTOR_EQUAL( 0, -1, -2, v2 );
  VECTOR_EQUAL( 0, -1, -2, v3 );
  
}

TEST(Vector, shouldProvideDotProduct) {

  Vector v1(5, 4, 2);
  Vector v2(1, 3, 4);

  DOUBLES_EQUAL( ((5*1)+(4*3)+(2*4)), v1.dot(v2), 0.0001 );

}


TEST(Vector, shouldProvideCrossProduct) {

  Vector v1(5, 4, 2);
  Vector v2(1, 3, 4);

  VECTOR_EQUAL(10, -18, 11, v1.cross(v2) );

}

TEST(Vector, shouldProvideUnaryMinus) {

  Vector v(1,-3,0);
  
  VECTOR_EQUAL( -1, 3, 0, (-v));

}

TEST(Vector, shouldProvideAddOperators) {

  Vector v1(1,-3,0);
  Vector v2(4, 4, 2);
  
  VECTOR_EQUAL( 5, 1, 2, (v1+v2));

  Vector v3 = v1 += v2;
  VECTOR_EQUAL( 5, 1, 2, v1);
  VECTOR_EQUAL( 5, 1, 2, v3);

}

TEST(Vector, shouldComputeLength) {

  Vector v( 3, 3, 2 );

  DOUBLES_EQUAL( 4.69041576, v.length(), 0.0001 );
  
}

TEST(Vector, shouldNormalize) {

  Vector v(2, 2, 2);

  VECTOR_EQUAL( 0.577350,0.577350,0.577350, v.normalize() );
  VECTOR_EQUAL( 0.577350,0.577350,0.577350, v );
}

TEST(Vector, shouldProvideMultiplyByScalar) {

  Vector v(1, 2, 3);
  
  VECTOR_EQUAL( 3, 6, 9, (v * 3) );

  Vector actual = (v *= 2);
  VECTOR_EQUAL( 2, 4, 6, actual );
  VECTOR_EQUAL( 2, 4, 6, v );

}
