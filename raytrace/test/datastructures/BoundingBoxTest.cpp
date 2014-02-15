#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
#include "BBox.h"


TEST_GROUP(BBox) {
	void setup() {}
	void teardown() {}
};

TEST(BBox, shouldBeSplittableInTheMiddle) {
 
  BoundingBox box(Matrix(-1,-1,-1), Matrix(2,2,2));
  
  BoundingBoxes boxes = box.split(0,0);

  VECTOR_EQUAL( -1,-1,-1, boxes.first.getOrigin() );
  VECTOR_EQUAL( 1,2,2, boxes.first.getDelta() );

  VECTOR_EQUAL( 0,-1,-1, boxes.second.getOrigin() );
  VECTOR_EQUAL( 1,2,2, boxes.second.getDelta() ); 
}

TEST(BBox, shouldBeSplittableOnSide) {
 
  BoundingBox box(Matrix(0,0,0), Matrix(2,2,2));
  
  BoundingBoxes boxes = box.split(0.25,1);

  VECTOR_EQUAL( 0,0,0, boxes.first.getOrigin() );
  VECTOR_EQUAL( 2,0.25,2, boxes.first.getDelta() );

  VECTOR_EQUAL( 0,0.25,0,  boxes.second.getOrigin() );
  VECTOR_EQUAL( 2,1.75,2, boxes.second.getDelta() ); 
}

TEST(BBox, shouldRefuteIntersectionOnX) {

  BoundingBox b1(Matrix(0, 0, 0), Matrix(1,1,1));
  BoundingBox bx(Matrix(0.5,10,10), Matrix(1,1,1));
  CHECK( !b1.intersects(bx) );

}

TEST(BBox, shouldRefuteIntersectionOnY) {

  BoundingBox b1(Matrix(0,0,0), Matrix(1,1,1));  
  BoundingBox by(Matrix(10,-1,10), Matrix(1,2,1));
  CHECK( !b1.intersects(by) );
}

TEST(BBox, shouldRefuteIntersectionOnZ) {

  BoundingBox b1(Matrix(0,0,0), Matrix(1,1,1));
    BoundingBox bz(Matrix(10,10,0), Matrix(1,1,1));
  CHECK( !b1.intersects(bz) );

}

TEST(BBox, shouldReportIntersectionOnContains) {

  BoundingBox b1(Matrix(0,0,0), Matrix(1,1,1));
  BoundingBox bo(Matrix(-1,-1,-1), Matrix(3,3,3));
  CHECK( b1.intersects(bo) );

}

TEST(BBox, shouldNotReportDisjointBoxes) {

  BoundingBox b1(Matrix(0,0,0), Matrix(1,1,1));
  BoundingBox b2(Matrix(2,2,2), Matrix(3,3,3));
 
  CHECK( ! b1.intersects(b2) );

}

TEST(BBox, shouldProvideUnion) {

  BoundingBox b1(Matrix(-1,0,10), Matrix(5, 7, 1));
  BoundingBox b2(Matrix(-3,3,11), Matrix(5, 2, 3));

  BoundingBox u = b1.unionWith(b2);

  VECTOR_EQUAL( -3, 0, 10, u.getOrigin() );
  VECTOR_EQUAL( 7, 7, 4, u.getDelta() );

}

TEST(BBox, shouldReturnCenterPoint) {

  BoundingBox b(Matrix(0,0,0), Matrix(10,10,10));
  
  Matrix c = b.center();

  VECTOR_EQUAL( 5,5,5, c );

}
