#include "CppUTest/CommandLineTestRunner.h"
#include "RTShapeFactory.h"
#include "scene_io.h"

#define COLOR_EQUAL(r,g,b, actual)              \
  CHECK_EQUAL(r, actual.getRGBRed());           \
  CHECK_EQUAL(g, actual.getRGBGreen());         \
  CHECK_EQUAL(b, actual.getRGBBlue());    

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
