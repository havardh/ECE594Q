#include "CppUTest/CommandLineTestRunner.h"
#include "RTSphere.h"
#include "RTTriangle.h"
#include "KDTree.h"

TEST_GROUP(KDTree) {
	void setup() {}
	void teardown() {}
};

TEST(KDTree, shouldDivideOnAverageByDefault) {
 
  KDTree tree;

  vector<RTShape*> shapes;
  RTSphere sphere0(Vector(-5,0,0), 1);
  RTSphere sphere1(Vector(5,0,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);

  BoundingBox box(Vector(-6, -1, -1), Vector(12, 2, 2));
  tree.setBoundingBox(box);
  tree.build(shapes, 0);

  KDTree *left = tree.getLeft();
  KDTree *right = tree.getRight();

  CHECK( left );
  CHECK( right );

  CHECK( left->isChild() );
  CHECK( right->isChild() );
  CHECK_EQUAL( 1, left->size() );
  CHECK_EQUAL( 1, right->size() );  
 
}

TEST(KDTree, shapesCanBeInTwoVoxelsIfOnEdge) {
 
  KDTree tree;

  vector<RTShape*> shapes;
  RTSphere sphere0(Vector(-5,0,0), 1);
  RTSphere sphere1(Vector(5,0,0), 1);
  RTSphere sphere2(Vector(0,0,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);
  shapes.push_back(&sphere2);

  BoundingBox box(Vector(-6, -1, -1), Vector(12, 2, 2));
  tree.setBoundingBox(box);
  tree.setTerminationCondition(2);
  tree.build(shapes, 0);

  CHECK_EQUAL( 2, tree.getLeft()->size() );
  CHECK_EQUAL( 2, tree.getRight()->size() ); 
}

TEST(KDTree, itSplitsXthenYthenZ) {

  KDTree tree;

  vector<RTShape*> shapes;
  RTSphere sphere0(Vector(5,5,0), 1);
  RTSphere sphere1(Vector(5,-5,0), 1);
  RTSphere sphere2(Vector(-5,5,0), 1);
  RTSphere sphere3(Vector(-5,-5,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);
  shapes.push_back(&sphere2);
  shapes.push_back(&sphere3);

  BoundingBox box(Vector(-6,-6,-6), Vector(12,12,12));
  tree.setBoundingBox(box);
  tree.setTerminationCondition(1);
  tree.build(shapes, 0);

  CHECK_EQUAL( 1, tree.getLeft()->getLeft()->size() );
  CHECK_EQUAL( 1, tree.getLeft()->getRight()->size() );
  CHECK_EQUAL( 1, tree.getRight()->getLeft()->size() );
  CHECK_EQUAL( 1, tree.getRight()->getRight()->size() );


}

TEST(KDTree, shouldSupportTriangles) {

  KDTree tree;
  vector<RTShape*> shapes;
  RTTriangle triangle0(Vector(0.1,0.1,0.1), Vector(1,1,1), Vector(0.1,2,0.1));
  RTTriangle triangle1(Vector(-0.1,-0.1,-0.1), Vector(-1,-1,-1), Vector(-0.1,-2,-0.1));
  shapes.push_back(&triangle0);
  shapes.push_back(&triangle1);

  BoundingBox box(Vector(-1,-2,-1), Vector(2,4,2));
  tree.setBoundingBox(box);
  tree.build(shapes, 0);
  
  CHECK_EQUAL( 1, tree.getLeft()->size() );
  CHECK_EQUAL( 1, tree.getRight()->size() );

}

TEST(KDTree, mixingTrianglesAndSphereIsNotAProblem) {
  
  KDTree tree;
  vector<RTShape*> shapes;
  RTTriangle triangle(Vector(0.1,0.1,0.1), Vector(1,1,1), Vector(0.1,2,0.1));
  RTSphere sphere(Vector(-1,-1,-1), 1);
  shapes.push_back(&triangle);
  shapes.push_back(&sphere);

  BoundingBox box(Vector(-2,-2,-2), Vector(2,4,2));
  tree.setBoundingBox(box);
  tree.build(shapes, 0);
  
  CHECK_EQUAL( 1, tree.getLeft()->size() );
  CHECK_EQUAL( 1, tree.getRight()->size() );

}

TEST(KDTree, shouldExtractTrianglesFromPolySet) {

  KDTree tree;
  
  vector<RTShape*> shapes;
  RTPolySet ps;
  RTTriangle t1(Vector(0,0,0), Vector(1,0,0), Vector(1,0,1));
  ps.addTriangle(t1);
  RTTriangle t2(Vector(5,5,5), Vector(6,6,5), Vector(6,6,6));
  ps.addTriangle(t2);
  shapes.push_back(&ps);

  BoundingBox box(Vector(0,0,0), Vector(6,6,6));
  tree.setBoundingBox(box);
  tree.setTerminationCondition(2);
  tree.build(shapes, 0);

  // This should'a been one with two.
  CHECK_EQUAL( 1, tree.getLeft()->size() );
  CHECK_EQUAL( 1, tree.getRight()->size() );

}

TEST(KDTree, shouldSupportIntersectionSearchForChildNode) {

  KDTree tree;
  
  vector<RTShape*> shapes;
  RTTriangle t1(Vector(0,0,0), Vector(0,1,0), Vector(0,0,1));
  RTTriangle t2(Vector(-1,0,0), Vector(-1,1,0), Vector(-1,0,1));
  shapes.push_back(&t1);
  shapes.push_back(&t2);

  BoundingBox box(Vector(0,0,0), Vector(1,0,1));
  tree.setBoundingBox(box);
  tree.setTerminationCondition(2);
  tree.build(shapes, 0);

  Ray ray(Vector(-5,0.1,0.1), Vector(1,0,0));
  IntersectionPtr intersection = tree.intersect(ray);
  
  CHECK( intersection->getShape() == &t2 );

}

TEST(KDTree, shouldSupportIntersectionSearchForRegularNodes) {

  KDTree tree;
  
  vector<RTShape*> shapes;
  RTSphere sphere0(Vector(5,5,0), 1);
  RTSphere sphere1(Vector(5,-5,0), 1);
  RTSphere sphere2(Vector(-5,5,0), 1);
  RTSphere sphere3(Vector(-5,-5,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);
  shapes.push_back(&sphere2);
  shapes.push_back(&sphere3);

  BoundingBox box(Vector(-6,-6,-6), Vector(12,12,12));
  tree.setBoundingBox(box);
  tree.setTerminationCondition(1);
  tree.build(shapes, 0);

  Ray ray(Vector(-10, 5, 0 ), Vector(1,0,0));
  IntersectionPtr intersection = tree.intersect(ray);
  
  CHECK( intersection != nullptr );
  CHECK( intersection->getShape() == &sphere2 );

}


