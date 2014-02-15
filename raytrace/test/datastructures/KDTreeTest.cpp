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
  RTSphere sphere0(Matrix(-5,0,0), 1);
  RTSphere sphere1(Matrix(5,0,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);

  BoundingBox box(Matrix(-6, -1, -1), Matrix(12, 2, 2));
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
  RTSphere sphere0(Matrix(-5,0,0), 1);
  RTSphere sphere1(Matrix(5,0,0), 1);
  RTSphere sphere2(Matrix(0,0,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);
  shapes.push_back(&sphere2);

  BoundingBox box(Matrix(-6, -1, -1), Matrix(12, 2, 2));
  tree.setBoundingBox(box);
  tree.setTerminationCondition(2);
  tree.build(shapes, 0);

  CHECK_EQUAL( 2, tree.getLeft()->size() );
  CHECK_EQUAL( 2, tree.getRight()->size() ); 
}

TEST(KDTree, itSplitsXthenYthenZ) {

  KDTree tree;

  vector<RTShape*> shapes;
  RTSphere sphere0(Matrix(5,5,0), 1);
  RTSphere sphere1(Matrix(5,-5,0), 1);
  RTSphere sphere2(Matrix(-5,5,0), 1);
  RTSphere sphere3(Matrix(-5,-5,0), 1);
  shapes.push_back(&sphere0);
  shapes.push_back(&sphere1);
  shapes.push_back(&sphere2);
  shapes.push_back(&sphere3);

  BoundingBox box(Matrix(-6,-6,-6), Matrix(12,12,12));
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
  RTTriangle triangle0(Matrix(0.1,0.1,0.1), Matrix(1,1,1), Matrix(0.1,2,0.1));
  RTTriangle triangle1(Matrix(-0.1,-0.1,-0.1), Matrix(-1,-1,-1), Matrix(-0.1,-2,-0.1));
  shapes.push_back(&triangle0);
  shapes.push_back(&triangle1);

  BoundingBox box(Matrix(-1,-2,-1), Matrix(2,4,2));
  tree.setBoundingBox(box);
  tree.build(shapes, 0);
  
  CHECK_EQUAL( 1, tree.getLeft()->size() );
  CHECK_EQUAL( 1, tree.getRight()->size() );

}

TEST(KDTree, mixingTrianglesAndSphereIsNotAProblem) {
  
  KDTree tree;
  vector<RTShape*> shapes;
  RTTriangle triangle(Matrix(0.1,0.1,0.1), Matrix(1,1,1), Matrix(0.1,2,0.1));
  RTSphere sphere(Matrix(-1,-1,-1), 1);
  shapes.push_back(&triangle);
  shapes.push_back(&sphere);

  BoundingBox box(Matrix(-2,-2,-2), Matrix(2,4,2));
  tree.setBoundingBox(box);
  tree.build(shapes, 0);
  
  CHECK_EQUAL( 1, tree.getLeft()->size() );
  CHECK_EQUAL( 1, tree.getRight()->size() );

}

TEST(KDTree, shouldExtractTrianglesFromPolySet) {

  KDTree tree;
  
  vector<RTShape*> shapes;
  RTPolySet ps;
  RTTriangle t1(Matrix(0,0,0), Matrix(1,0,0), Matrix(1,0,1));
  ps.addTriangle(t1);
  RTTriangle t2(Matrix(5,5,5), Matrix(6,6,5), Matrix(6,6,6));
  ps.addTriangle(t2);
  shapes.push_back(&ps);

  BoundingBox box(Matrix(0,0,0), Matrix(6,6,6));
  tree.setBoundingBox(box);
  tree.setTerminationCondition(2);
  tree.build(shapes, 0);

  // This should'a been one with two.
  CHECK_EQUAL( 1, tree.getLeft()->size() );
  CHECK_EQUAL( 1, tree.getRight()->size() );

}
