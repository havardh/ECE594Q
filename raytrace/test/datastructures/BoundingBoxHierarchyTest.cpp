#include "CppUTest/CommandLineTestRunner.h"
#include "BoundingBoxHierarchy.h"

#include "RTSphere.h"
#include "RTPolySet.h"
#include "RTTriangle.h"

TEST_GROUP(BoundingBoxHierarchy) {
	void setup() {}
	void teardown() {}
};

TEST(BoundingBoxHierarchy, shouldFindObject) {
  
  BoundingBoxHierarchy bbh;

  vector<RTShape*> shapes;
  RTSphere sphere0(Vector(-5,0,0), 1);
  RTSphere sphere1(Vector(5,0,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);

  bbh.build(shapes);

  IntersectionPtr I0 = bbh.intersect(Ray(Vector(-5, 0, -2),Vector(0,0,1)));
  CHECK( I0 != nullptr );
  CHECK( I0->getShape() == &sphere0 );

  IntersectionPtr I1 = bbh.intersect(Ray(Vector(5, 0, -2),Vector(0,0,1)));
  CHECK( I1 != nullptr );
  CHECK( I1->getShape() == &sphere1 );

}


TEST(BoundingBoxHierarchy, shouldExtractTrianglesFromPolySet) {

  BoundingBoxHierarchy bbh;
  
  vector<RTShape*> shapes;
  RTPolySet ps;
  RTTriangle t1(Vector(0,0,0), Vector(1,0,0), Vector(1,0,1));
  ps.addTriangle(t1);
  RTTriangle t2(Vector(5,5,5), Vector(6,6,5), Vector(6,6,6));
  ps.addTriangle(t2);
  shapes.push_back(&ps);

  bbh.build(shapes);

  // This should'a been one with two.
  CHECK( bbh.getLeft()->getShape() );
  CHECK( bbh.getRight()->getShape() );

}
