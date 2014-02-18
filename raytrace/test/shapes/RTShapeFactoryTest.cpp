#include "CppUTest/CommandLineTestRunner.h"
#include "RTShapeFactory.h"
#include "MatrixTestHelper.h"
#include "ColorTestHelper.h"
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
    {0,1,1},
    {0.5f,0,0},
    {0,0,0.3f},
    {0,0.7f,0},
    4, 2,
  },{
    {0,1,1},
    {0.5f,0,0},
    {0,0,0.3f},
    {0,0.7f,0},
    4, 2,
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

  DOUBLES_EQUAL(5, sphere->getOrigin().x(), 0.0001);
  DOUBLES_EQUAL(-1, sphere->getOrigin().y(), 0.0001);
  DOUBLES_EQUAL(7, sphere->getOrigin().z(), 0.0001);
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
  
  Vector p0 = triangle.getP0();
  DOUBLES_EQUAL(0, p0.x(), 0.0001);
  DOUBLES_EQUAL(0, p0.y(), 0.0001);
  DOUBLES_EQUAL(0, p0.z(), 0.0001);

  Vector p1 = triangle.getP1();
  DOUBLES_EQUAL(1, p1.x(), 0.0001);
  DOUBLES_EQUAL(1, p1.y(), 0.0001);
  DOUBLES_EQUAL(1, p1.z(), 0.0001);

  Vector p2 = triangle.getP2();
  DOUBLES_EQUAL(1, p2.x(), 0.0001);
  DOUBLES_EQUAL(0, p2.y(), 0.0001);
  DOUBLES_EQUAL(2, p2.z(), 0.0001);

  delete set;
  
}

TEST(RTShapeFactory, shouldCreateMaterial) {
  
  RTMaterial material = RTShapeFactory::createMaterial(materialIO);
  (void) material;

  COLOR_EQUAL(0,255,255, material.getDiffColor());
  COLOR_EQUAL(127,0,0, material.getAmbColor());
  COLOR_EQUAL(0,0,76, material.getSpecColor());  
  COLOR_EQUAL(0,178,0, material.getEmissColor());
  DOUBLES_EQUAL(4, material.getShininess(), 0.0001);
  DOUBLES_EQUAL(2, material.getKTransparency(), 0.0001);
}

TEST(RTShapeFactory, shouldCreateShapeWithMaterials) {
  
  ObjIO obj = {
    0, 0, 2,
    materialIO,
    SPHERE_OBJ,
    &sphereIO
  };

  RTShape *shape = (RTShape*)RTShapeFactory::createShape(&obj);

  CHECK_EQUAL(2, shape->getMaterialCount());

  delete shape;
  
}

TEST(RTShapeFactory, polygonsShouldInheritMaterials) {
  
  ObjIO obj = {
    0,0,1,
    materialIO,
    POLYSET_OBJ,
    &polySetIO
  };

  RTPolySet *polySet = (RTPolySet*)RTShapeFactory::createShape(&obj);
  RTTriangle triangle = polySet->getTriangle(0);

  CHECK_EQUAL(1, triangle.getMaterialCount());
  
  delete polySet;
}

TEST(RTShapeFactory, shouldCreateXPlane) {

  BoundingBox b(Vector(3,2,1), Vector(10,10,10));

  RTPlane plane = RTShapeFactory::createPlane(b, 0, 10);
  RTTriangle t1 = plane.getTriangle(0);
  RTTriangle t2 = plane.getTriangle(1);
 
  VECTOR_EQUAL( 10, 2, 1, t1.getP0());
  VECTOR_EQUAL( 10, 12, 1, t1.getP1());
  VECTOR_EQUAL( 10, 12, 11, t1.getP2());

  VECTOR_EQUAL( 10, 2, 1, t2.getP0());
  VECTOR_EQUAL( 10, 2, 11, t2.getP1());
  VECTOR_EQUAL( 10, 12, 11, t2.getP2());
 
}

TEST(RTShapeFactory, shouldCreateYPlane) {

  BoundingBox b(Vector(3,4,2), Vector(10,14,5));

  RTPlane plane = RTShapeFactory::createPlane(b, 1, 7);
  RTTriangle t1 = plane.getTriangle(0);
  RTTriangle t2 = plane.getTriangle(1);
 
  VECTOR_EQUAL( 3, 7, 2, t1.getP0());
  VECTOR_EQUAL( 3, 7, 7, t1.getP1());
  VECTOR_EQUAL( 13, 7, 7, t1.getP2());

  VECTOR_EQUAL( 3, 7, 2, t2.getP0());
  VECTOR_EQUAL( 13, 7, 2, t2.getP1());
  VECTOR_EQUAL( 13, 7, 7, t2.getP2());
 
}

TEST(RTShapeFactory, shouldCreateZPlane) {

  BoundingBox b(Vector(3,4,2), Vector(10,14,5));

  RTPlane plane = RTShapeFactory::createPlane(b, 2, 7);
  RTTriangle t1 = plane.getTriangle(0);
  RTTriangle t2 = plane.getTriangle(1);
 
  VECTOR_EQUAL( 3, 4, 7, t1.getP0());
  VECTOR_EQUAL( 3, 18, 7, t1.getP1());
  VECTOR_EQUAL( 13, 18, 7, t1.getP2());

  VECTOR_EQUAL( 3, 4, 7, t2.getP0());
  VECTOR_EQUAL( 13, 4, 7, t2.getP1());
  VECTOR_EQUAL( 13, 18, 7, t2.getP2());
 
}
