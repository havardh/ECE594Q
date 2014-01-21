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
  MeshMock(float * values, int n) : Mesh(2) {
    
    for (int i=0; i<n; i++) { 
      this->mesh[i].setAll(&values[i*4]);
    }
  }
  
};

static float values[] = {
  -1, -1, -1, 1,
  1, 1, 1, 1,

  -1, 2, 1, 1,
  2, -3, 1, 1
};

TEST(Mesh, shouldComputeBoundingBox) {


	Mesh *m = new MeshMock(values, 2);

  BoundingBox box = m->getBoundingBox();

  DOUBLES_EQUAL(-1, box.getX(), 0.0001);
  DOUBLES_EQUAL(-1, box.getY(), 0.0001);
  DOUBLES_EQUAL(2, box.getDX(), 0.0001);
  DOUBLES_EQUAL(2, box.getDY(), 0.0001);

  delete m;
}

TEST(Mesh, shouldProjectOnto) {

  
  Mesh *m = new MeshMock(values, 2);
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


TEST(Mesh, shouldDiceIntoMicropolygons) {
  
	MeshMock mesh(values, 4);
  std::vector<Micropolygon> polygon = mesh.getMicropolygons();

  Matrix  m1 = polygon[0].get(0);
  Matrix  m2 = polygon[0].get(1);
  Matrix  m3 = polygon[0].get(2);
  Matrix  m4 = polygon[0].get(3);
  
  MATRIX_EQUALS(&values[0], m1, 0.0001);
  MATRIX_EQUALS(&values[4], m2, 0.0001);
  MATRIX_EQUALS(&values[8], m3, 0.0001);
  MATRIX_EQUALS(&values[12], m4, 0.0001);

  //delete polygon;
  (void)polygon;
  
}


