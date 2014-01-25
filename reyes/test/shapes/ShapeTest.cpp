#include "CppUTest/CommandLineTestRunner.h"
#include "Shape.h"
#include "MatrixTestHelper.h"
#include "ShapeMock.h"

TEST_GROUP(Shape) {
  void setup() {}
  void teardown() {}
};



/**
 * Checks if the given polygon has the values from the position valueIndex from valuesArray on position i
 */
static void CHECK_DICING(Polygon polygon, int *valueIndices, float *valuesArray) {

  for (int i=0; i<4; i++) {
      Matrix m = *polygon.get(i);
      MATRIX_EQUALS(&valuesArray[valueIndices[i]], m, 0.0001);
  }
  
}

static float values[] = {
  -1, -1, -1, 1,
  1, 1, 1, 1,

  -1, 2, 1, 1,
  2, -3, 1, 1,
};


TEST(Shape, shouldDiceIntoPolygons) {
  
	ShapeMock shape(values, 2, 2);
  std::vector<Polygon> polygon = shape.getPolygons();

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
  std::vector<Polygon> polygons = shape.getPolygons();

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


TEST(Shape, shouldPassOnMeshPointColorToPolygon) {
  
  float v[] = { 
    1,1,1,1,  
    1,1,1,1,  
    1,1,1,1,  
    1,1,1,1,  
    1,1,1,1,  
    1,1,1,1,  
    1,1,1,1,  
    1,1,1,1,  
    1,1,1,1
  };
	ShapeMock m(v, 3, 3);
  Color c[]  = {
    { 1,1,1 },
    { 2,2,2 },
    { 3,3,3 },
    { 4,4,4 },
    { 5,5,5 },
    { 6,6,6 },
    { 7,7,7 },
    { 8,8,8 },
    { 9,9,9 }
  };
  m.getMeshPoint(0,0).color = c[0];
  m.getMeshPoint(0,1).color = c[1];
  m.getMeshPoint(0,2).color = c[2];
  m.getMeshPoint(1,0).color = c[3];
  m.getMeshPoint(1,1).color = c[4];
  m.getMeshPoint(1,2).color = c[5];
  
  std::vector<Polygon> P = m.getPolygons();

  CHECK_EQUAL(c[0].red,   P[(size_t)0].getColor().red);
  CHECK_EQUAL(c[0].green, P[(size_t)0].getColor().green);
  CHECK_EQUAL(c[0].blue,  P[(size_t)0].getColor().blue);

  CHECK_EQUAL(c[1].red,   P[(size_t)1].getColor().red);
  CHECK_EQUAL(c[1].green, P[(size_t)1].getColor().green);
  CHECK_EQUAL(c[1].blue,  P[(size_t)1].getColor().blue);

  CHECK_EQUAL(c[2].red,   P[(size_t)2].getColor().red);
  CHECK_EQUAL(c[2].green, P[(size_t)2].getColor().green);
  CHECK_EQUAL(c[2].blue,  P[(size_t)2].getColor().blue);

  CHECK_EQUAL(c[3].red,   P[(size_t)3].getColor().red);
  CHECK_EQUAL(c[3].green, P[(size_t)3].getColor().green);
  CHECK_EQUAL(c[3].blue,  P[(size_t)3].getColor().blue);

  CHECK_EQUAL(c[4].red,   P[(size_t)4].getColor().red);
  CHECK_EQUAL(c[4].green, P[(size_t)4].getColor().green);
  CHECK_EQUAL(c[4].blue,  P[(size_t)4].getColor().blue);

  CHECK_EQUAL(c[5].red,   P[(size_t)5].getColor().red);
  CHECK_EQUAL(c[5].green, P[(size_t)5].getColor().green);
  CHECK_EQUAL(c[5].blue,  P[(size_t)5].getColor().blue);
}



TEST(Shape, shouldContainTextureCoordinates) {
  
  float v[10*10*4];
  ShapeMock s(v, 10, 10);

  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      MeshPoint p = s.getMeshPoint(i,j);
      DOUBLES_EQUAL(i/10.0, p.u, 0.0001);
      DOUBLES_EQUAL(j/10.0, p.v, 0.0001);
    }
  }
   
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

// Test Spy
static float su[16], sv[16];
static int shaderCallCount = 0;
void shadeMock(ShaderParam param) {
  su[shaderCallCount] = param.u;
  sv[shaderCallCount] = param.v;
  shaderCallCount++;
}

TEST(Shape, shouldHandleNoShader) {

  float v[] = { 1,1,1,1 };
  ShapeMock s(v, 1, 1);
  
  s.shade(NULL);
  
}

TEST(Shape, shouldCallShaderForEachCoordinate) {

  // Dont care but lets set up som mem
  float v[] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
  };
  ShapeMock s(v,4,4);

  s.shade(&shadeMock);

  CHECK_EQUAL(16, shaderCallCount);
  DOUBLES_EQUAL(0.0000, su[0], 0.0001);
  DOUBLES_EQUAL(0.0000, sv[0], 0.0001);
  DOUBLES_EQUAL(0.0000, su[1], 0.0001);
  DOUBLES_EQUAL(0.3333, sv[1], 0.0001);
  DOUBLES_EQUAL(0.0000, su[2], 0.0001);
  DOUBLES_EQUAL(0.6666, sv[2], 0.0001);
  DOUBLES_EQUAL(0.0000, su[3], 0.0001);
  DOUBLES_EQUAL(1.0000, sv[3], 0.0001);

  DOUBLES_EQUAL(0.3333, su[4+0], 0.0001);
  DOUBLES_EQUAL(0.0000, sv[4+0], 0.0001);
  DOUBLES_EQUAL(0.3333, su[4+1], 0.0001);
  DOUBLES_EQUAL(0.3333, sv[4+1], 0.0001);
  DOUBLES_EQUAL(0.3333, su[4+2], 0.0001);
  DOUBLES_EQUAL(0.6666, sv[4+2], 0.0001);
  DOUBLES_EQUAL(0.3333, su[4+3], 0.0001);
  DOUBLES_EQUAL(1.0000, sv[4+3], 0.0001);

  DOUBLES_EQUAL(0.6666, su[8+0], 0.0001);
  DOUBLES_EQUAL(0.0000, sv[8+0], 0.0001);
  DOUBLES_EQUAL(0.6666, su[8+1], 0.0001);
  DOUBLES_EQUAL(0.3333, sv[8+1], 0.0001);
  DOUBLES_EQUAL(0.6666, su[8+2], 0.0001);
  DOUBLES_EQUAL(0.6666, sv[8+2], 0.0001);
  DOUBLES_EQUAL(0.6666, su[8+3], 0.0001);
  DOUBLES_EQUAL(1.0000, sv[8+3], 0.0001);

  DOUBLES_EQUAL(1.0000, su[12+0], 0.0001);
  DOUBLES_EQUAL(0.0000, sv[12+0], 0.0001);
  DOUBLES_EQUAL(1.0000, su[12+1], 0.0001);
  DOUBLES_EQUAL(0.3333, sv[12+1], 0.0001);
  DOUBLES_EQUAL(1.0000, su[12+2], 0.0001);
  DOUBLES_EQUAL(0.6666, sv[12+2], 0.0001);
  DOUBLES_EQUAL(1.0000, su[12+3], 0.0001);
  DOUBLES_EQUAL(1.0000, sv[12+3], 0.0001);


}
