#include "CppUTest/CommandLineTestRunner.h"
#include "Shape.h"
#include "MatrixTestHelper.h"

TEST_GROUP(Shape) {
  void setup() {}
  void teardown() {}
};

class ShapeMock : public Shape {

public:
  ShapeMock(float * values, int m, int n) : Shape(m, n) {
    
    for (int i=0; i<m*n; i++) { 
      this->mesh[(size_t)i].setAll(&values[i*4]);
    }
  }
  
};

/**
 * Checks if the given polygon has the values from the position valueIndex from valuesArray on position i
 */
static void CHECK_DICING(Micropolygon polygon, int *valueIndices, float *valuesArray) {

  for (int i=0; i<4; i++) {
      Matrix m = polygon.get(i);
      MATRIX_EQUALS(&valuesArray[valueIndices[i]], m, 0.0001);
  }
  
}

static float values[] = {
  -1, -1, -1, 1,
  1, 1, 1, 1,

  -1, 2, 1, 1,
  2, -3, 1, 1,
};


TEST(Shape, shouldDiceIntoMicropolygons) {
  
	ShapeMock shape(values, 2, 2);
  std::vector<Micropolygon> polygon = shape.getMicropolygons();

  int valuesArray[] = { 0, 4, 8, 12 };
  CHECK_DICING(polygon[0], valuesArray, values);
  
}

static float grid[] = {
  -1,  1, -1,1,
   0,  1,  0,1,
   1,  1,  1,1,

  -1,  0, -1,1,
   0,  0,  0,1,
   1,  0,  1,1,

  -1, -1, -1,1,
   0, -1,  0,1,
   1, -1,  1,1
  
};

TEST(Shape, dicingShouldBeSequential) {
  
	ShapeMock shape(grid, 3, 3);
  std::vector<Micropolygon> polygons = shape.getMicropolygons();

  CHECK_EQUAL(6, polygons.size());
  /*
  int v1[] = { 0, 4, 12, 16 };
  CHECK_DICING(polygons[0], v1, grid);

  int v2[] = { 4, 8, 16, 20 };
  CHECK_DICING(polygons[1], v2, grid);

  int v3[] = { 12, 16, 24, 28 };
  CHECK_DICING(polygons[2], v3, grid);

  int v4[] = { 16, 20, 28, 32 };
  CHECK_DICING(polygons[3], v4, grid);
  */
}



TEST(Shape, shouldSetGetColor) {
  
	Shape s;
  s.setColor(1, 2, 3);
  Color c = s.getColor();
  CHECK_EQUAL(1, c.red);
  CHECK_EQUAL(2, c.green);
  CHECK_EQUAL(3, c.blue);
  
}


TEST(Shape, shouldSetOpacity) {
  
	Shape s;
  s.setOpacity(0.5);
  DOUBLES_EQUAL(0.5, s.getOpacity(), 0.0001);
  
}

