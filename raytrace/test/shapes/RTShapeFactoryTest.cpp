#include "CppUTest/CommandLineTestRunner.h"
#include "RTShapeFactory.h"
#include "scene_io.h"

static SphereIO sphereIO = {
  {5,-1,7}, 3,
  {0,0,0}, 0,
  {0,0,0}, 0,
  {0,0,0}, 0
};

static VertexIO vertexIO[] = {{
    { 0, 0, 0 }, 
    { 0, 0, 0 },
    0,0,0
  },{
    { 1, 1, 1 }, 
    { 0, 0, 0 },
    0,0,0
  },{
    { 1, 0, 2 }, 
    { 0, 0, 0 },
    0,0,0
  }};

static PolygonIO polygonIO[] = {{
  3, vertexIO
  }};

static PolySetIO polySetIO = {
  POLYSET_TRI_MESH, PER_VERTEX_NORMAL, PER_OBJECT_MATERIAL, 0,
  1, 1, polygonIO
};

static MaterialIO materialIO[] = {{
    {0,0,0},
    {0,0,0},
    {0,0,0},
    {0,0,0},
    0, 0,
  }};


TEST_GROUP(RTShapeFactory) {
	void setup() {}
	void teardown() {}
};

TEST(RTShapeFactory, shouldCreateASphere) {
 

  ObjIO obj = {
    0, 0, 1,
    materialIO,
    SPHERE_OBJ,
    &sphereIO
  };

  RTSphere *sphere = (RTSphere*)RTShapeFactory::createShape(&obj);

  CHECK(sphere && typeid(*sphere) == typeid(RTSphere));

  DOUBLES_EQUAL(5, sphere->getOrigin().get(0), 0.0001);
  DOUBLES_EQUAL(-1, sphere->getOrigin().get(1), 0.0001);
  DOUBLES_EQUAL(7, sphere->getOrigin().get(2), 0.0001);
  DOUBLES_EQUAL(3, sphere->getRadius(), 0.0001);

  delete sphere;
}

TEST(RTShapeFactory, shouldCreateATriangle) {
  
	ObjIO obj = {
    0,0,1,
    materialIO,
    POLYSET_OBJ,
    &polySetIO
  };

  RTPolySet *set = (RTPolySet*) RTShapeFactory::createShape(&obj);
  CHECK(set && typeid(*set) == typeid(RTPolySet));
  RTTriangle triangle = set->getTriangle(0);

  CHECK(typeid(triangle) == typeid(RTTriangle));
  
  Matrix p0 = triangle.getP0();
  DOUBLES_EQUAL(0, p0.get(0), 0.0001);
  DOUBLES_EQUAL(0, p0.get(1), 0.0001);
  DOUBLES_EQUAL(0, p0.get(2), 0.0001);

  Matrix p1 = triangle.getP1();
  DOUBLES_EQUAL(1, p1.get(0), 0.0001);
  DOUBLES_EQUAL(1, p1.get(1), 0.0001);
  DOUBLES_EQUAL(1, p1.get(2), 0.0001);

  Matrix p2 = triangle.getP2();
  DOUBLES_EQUAL(1, p2.get(0), 0.0001);
  DOUBLES_EQUAL(0, p2.get(1), 0.0001);
  DOUBLES_EQUAL(2, p2.get(2), 0.0001);

  delete set;
  
}
