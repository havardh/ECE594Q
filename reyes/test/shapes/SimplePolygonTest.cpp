#include "CppUTest/CommandLineTestRunner.h"
#include "SimplePolygon.h"
#include "MatrixTestHelper.h"

TEST_GROUP(SimplePolygon) {
  void setup() {}
  void teardown() {}
};


TEST(SimplePolygon, shouldCreateASimplePolygonFromAPolygon) {
  
  Micropolygon p;
  p.set(0, Matrix(1,1,0,1));
  p.set(1, Matrix(-1,-1,0,1));
  p.set(2, Matrix(-1,1,0,1));
  p.set(3, Matrix(1,-1,0,1));

  SimplePolygon sp(p);
  
  float values [] = {
    -1,-1,0,1,
    1,1,0,1,
    1,-1,0,1,
    -1,1,0,1
  };

  MATRIX_EQUALS(&values[4*3], sp.get(0), 0.0001);
  MATRIX_EQUALS(&values[4*1], sp.get(1), 0.0001);
  MATRIX_EQUALS(&values[4*2], sp.get(2), 0.0001);
  MATRIX_EQUALS(&values[4*0], sp.get(3), 0.0001);
  
}

TEST(SimplePolygon, shouldFixBug1) {

  Micropolygon p;
  p.set(0, Matrix(0.10180739f, 0.14012584f, 0.99099100f, 1.00000000f));
  p.set(1, Matrix(0.07961334f, 0.13544630f, 0.99132532f, 1.00000000f));
  p.set(2, Matrix(0.14012584f, 0.10180739f, 0.99099100f, 1.00000000f));
  p.set(3, Matrix(0.10821813f, 0.09718592f, 0.99144536f, 1.00000000f));

  SimplePolygon sp(p);

  float values [] = {
    0.10180739f, 0.14012584f, 0.99099100f, 1.00000000f,
    0.14012584f, 0.10180739f, 0.99099100f, 1.00000000f,
    0.10821813f, 0.09718592f, 0.99144536f, 1.00000000f,
    0.07961334f, 0.13544630f, 0.99132532f, 1.00000000f
  };

  MATRIX_EQUALS(&values[4*0], sp.get(0), 0.0001);
  MATRIX_EQUALS(&values[4*1], sp.get(1), 0.0001);
  MATRIX_EQUALS(&values[4*2], sp.get(2), 0.0001);
  MATRIX_EQUALS(&values[4*3], sp.get(3), 0.0001);

}

IGNORE_TEST(SimplePolygon, shouldFixBug2) {

  Micropolygon p;
  p.set(0, Matrix(0.02459044f, 0.01237137f, 0.99188828f, 1.00000000f));
  p.set(1, Matrix(-0.00000001f, 0.01235756f, 0.99189842f, 1.00000000f));
  p.set(2, Matrix(0.02465964f, -0.00000001f, 0.99189079f, 1.00000000f));
  p.set(3, Matrix(-0.00000001f, -0.00000001f, 0.99190098f, 1.00000000f));

  SimplePolygon sp(p);

  float values [] = {
    0.02459044f,  0.01237137f, 0.99188828f, 1.00000000f,
    0.02465964f, -0.00000001f, 0.99189079f, 1.00000000f,
    -0.00000001f, -0.00000001f, 0.99190098f, 1.00000000f,
    -0.00000001f, 0.01235756f, 0.99189842f, 1.00000000f
  };

  MATRIX_EQUALS(&values[4*0], sp.get(0), 0.0001);
  MATRIX_EQUALS(&values[4*1], sp.get(1), 0.0001);
  MATRIX_EQUALS(&values[4*2], sp.get(2), 0.0001);
  MATRIX_EQUALS(&values[4*3], sp.get(3), 0.0001);

}
