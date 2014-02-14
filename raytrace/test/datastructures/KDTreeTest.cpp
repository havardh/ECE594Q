#include "CppUTest/CommandLineTestRunner.h"
#include "RTSphere.h"
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

