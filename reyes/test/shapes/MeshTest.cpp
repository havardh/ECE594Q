#include "CppUTest/CommandLineTestRunner.h"
#include "Mesh.h"
#include "Sphere.h"
#include "Matrix.h"
#include "MatrixFactory.h"
#include "MatrixTestHelper.h"
#include <cmath>
#include <vector>

TEST_GROUP(Mesh) {
  void setup() {}
  void teardown() {}
};
 
class MeshMock : public Mesh {

public:
  MeshMock(float * values, int m, int n) : Mesh(m, n) {
    
    for (int i=0; i<m*n; i++) { 
      this->mesh[(size_t)i].setAll(&values[i*4]);
    }
  }
  
};

static float values[] = {
  -1, -1, -1, 1,
  1, 1, 1, 1,

  -1, 2, 1, 1,
  2, -3, 1, 1,
};

TEST(Mesh, shouldSupportAssignmentOperator) {
  
  float v[] = { 1, 1, 1, 2 };
  Mesh *m = new MeshMock(v, 1, 1);

  Mesh m2 = *m;
  m->homogenize();


  MATRIX_EQUALS(v, m2.getPoint(0), 0.0001);

  float v2[] = { 0.5f, 0.5f, 0.5f, 1.0 };
  MATRIX_EQUALS(v2, m->getPoint(0), 0.0001);

  delete m;
}

TEST(Mesh, shouldComputeBoundingBox) {


	Mesh *m = new MeshMock(values, 2, 2);

  BoundingBox box = m->getBoundingBox();

  DOUBLES_EQUAL(-1, box.getX(), 0.0001);
  DOUBLES_EQUAL(-3, box.getY(), 0.0001);
  DOUBLES_EQUAL(3, box.getDX(), 0.0001);
  DOUBLES_EQUAL(5, box.getDY(), 0.0001);

  delete m;
}

TEST(Mesh, shouldProjectOnto) {

  
  Mesh *m = new MeshMock(values, 2, 2);
  Matrix projectionMatrix = MatrixFactory::createPerspectiveProjection(
    (float)(M_PI/3.0), 4.0f/4.0f, 1, 1000
  );

  m->projectOnto(projectionMatrix);
  m->homogenize();


  Matrix m1 = m->getPoint(0);  
  float ex1[] = { 1.7321f, 1.7321f, 2.002f, 1 };
  MATRIX_EQUALS(ex1, m1, 0.0001);
  
  Matrix m2 = m->getPoint(1);
  float ex2[] = { 1.7321f, 1.7321f, 0, 1 };
  MATRIX_EQUALS(ex2, m2, 0.0001);
  
  delete m;
}

/**
 * Checks if the given polygon has the values from the position valueIndex from valuesArray on position i
 */
void CHECK_DICING(Micropolygon polygon, int *valueIndices, float *valuesArray) {

  for (int i=0; i<4; i++) {
      Matrix m = polygon.get(i);
      MATRIX_EQUALS(&valuesArray[valueIndices[i]], m, 0.0001);
  }
  
}

TEST(Mesh, shouldDiceIntoMicropolygons) {
  
	MeshMock mesh(values, 2, 2);
  std::vector<Micropolygon> polygon = mesh.getMicropolygons();

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

TEST(Mesh, dicingShouldBeSequential) {
  
	MeshMock mesh(grid, 3, 3);
  std::vector<Micropolygon> polygons = mesh.getMicropolygons();

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
