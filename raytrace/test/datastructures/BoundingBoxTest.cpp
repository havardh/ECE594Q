#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
#include "BBox.h"


TEST_GROUP(BBox) {
	void setup() {}
	void teardown() {}
};

TEST(BBox, shouldBeSplittableInTheMiddle) {
 
  BoundingBox box(Vector(-1,-1,-1), Vector(2,2,2));
  
  BoundingBoxes boxes = box.split(0,0);

  VECTOR_EQUAL( -1,-1,-1, boxes.first.getOrigin() );
  VECTOR_EQUAL( 1,2,2, boxes.first.getDelta() );

  VECTOR_EQUAL( 0,-1,-1, boxes.second.getOrigin() );
  VECTOR_EQUAL( 1,2,2, boxes.second.getDelta() ); 
}

TEST(BBox, shouldBeSplittableOnSide) {
 
  BoundingBox box(Vector(0,0,0), Vector(2,2,2));
  
  BoundingBoxes boxes = box.split(0.25,1);

  VECTOR_EQUAL( 0,0,0, boxes.first.getOrigin() );
  VECTOR_EQUAL( 2,0.25,2, boxes.first.getDelta() );

  VECTOR_EQUAL( 0,0.25,0,  boxes.second.getOrigin() );
  VECTOR_EQUAL( 2,1.75,2, boxes.second.getDelta() ); 
}

TEST(BBox, shouldRefuteIntersectionOnX) {

  BoundingBox b1(Vector(0, 0, 0), Vector(1,1,1));
  BoundingBox bx(Vector(0.5,10,10), Vector(1,1,1));
  CHECK( !b1.intersects(bx) );

}

TEST(BBox, shouldRefuteIntersectionOnY) {

  BoundingBox b1(Vector(0,0,0), Vector(1,1,1));  
  BoundingBox by(Vector(10,-1,10), Vector(1,2,1));
  CHECK( !b1.intersects(by) );
}

TEST(BBox, shouldRefuteIntersectionOnZ) {

  BoundingBox b1(Vector(0,0,0), Vector(1,1,1));
    BoundingBox bz(Vector(10,10,0), Vector(1,1,1));
  CHECK( !b1.intersects(bz) );

}

TEST(BBox, shouldReportIntersectionOnContains) {

  BoundingBox b1(Vector(0,0,0), Vector(1,1,1));
  BoundingBox bo(Vector(-1,-1,-1), Vector(3,3,3));
  CHECK( b1.intersects(bo) );

}

TEST(BBox, shouldNotReportDisjointBoxes) {

  BoundingBox b1(Vector(0,0,0), Vector(1,1,1));
  BoundingBox b2(Vector(2,2,2), Vector(3,3,3));
 
  CHECK( ! b1.intersects(b2) );

}

TEST(BBox, shouldProvideUnion) {

  BoundingBox b1(Vector(-1,0,10), Vector(5, 7, 1));
  BoundingBox b2(Vector(-3,3,11), Vector(5, 2, 3));

  BoundingBox u = b1.unionWith(b2);

  VECTOR_EQUAL( -3, 0, 10, u.getOrigin() );
  VECTOR_EQUAL( 7, 7, 4, u.getDelta() );

}

TEST(BBox, shouldReturnCenterPoint) {

  BoundingBox b(Vector(0,0,0), Vector(10,10,10));
  
  Vector c = b.center();

  VECTOR_EQUAL( 5,5,5, c );

}

TEST(BBox, shouldReturnIntersections) {

  BoundingBox b(Vector(2,2,2), Vector(2, 2, 2));
  Ray r(Vector(0,0,0), Vector(1,1,1));
  
  float t0, t1;
  CHECK( b.intersects(r, t0, t1) );

  DOUBLES_EQUAL(2, t0, 0.0001);
  DOUBLES_EQUAL(4, t1, 0.0001);

}

TEST(BBox, shouldReturnIntersectionsForRayWithZeroDirections) {

  BoundingBox b(Vector(2,2,2), Vector(2, 2, 2));
  Ray r(Vector(1,1,0), Vector(0,0,1));
  
  float t0, t1;
  CHECK( b.intersects(r, t0, t1) );

  DOUBLES_EQUAL(2, t0, 0.0001);
  DOUBLES_EQUAL(4, t1, 0.0001);

}

TEST(BBox, shouldReturnFalseWhenNotIntersection) {

  BoundingBox b(Vector(2,2,2), Vector(2, 2, 2));
  Ray r(Vector(5,5,0), Vector(0,0,1));
  
  float t0, t1;
  CHECK( !b.intersects(r, t0, t1) );


}

