#include "CppUTest/CommandLineTestRunner.h"
#include "ShapeTestHelper.h"
#include "RTTriangle.h"
#include "RTShapeFactory.h"
#include "Matrix.h"
#include <vector>

TEST_GROUP(RTTriangle) {
	void setup() {}
	void teardown() {}
};

TEST(RTTriangle, shouldCheckForIntersection) {
  
  RTTriangle triangle(Matrix(1,1,20), Matrix(2,1,40), Matrix(2,2,10));

  CHECK(triangle.intersect(Ray(Matrix(1,1,0), Matrix(0,0,1))) != nullptr);
  CHECK(triangle.intersect(Ray(Matrix(0,1,0), Matrix(0,0,1))) == nullptr);

}

TEST(RTTriangle, shouldReturnIntersectionPoint) {

  RTTriangle t(Matrix(-2,-2,10), Matrix(2,0,10), Matrix(-2,2,10));
  CHECK_INTERSECTS_AT(t, Ray(Matrix(0,0,0), Matrix(0,0,1)), 0,0,10);

}

TEST(RTTriangle, shouldReturnIntersectionPointOnARotatedTriangle) {

  RTTriangle t(Matrix(-2,-2,20), Matrix(2,0,20), Matrix(-2,2,10));
  CHECK_INTERSECTS_AT(t, Ray(Matrix(0,0,0), Matrix(0,0,1)), 0,0,17.5f);

}

TEST(RTTriangle, shouldReturnSurfaceNormalInDirectionOfTheRay) {

  RTTriangle t(Matrix(-2,-2,10), Matrix(2,0,10), Matrix(-2,2,10));
  CHECK_NORMAL_AT(t, Matrix(0,0,10), Matrix(0,0,0), 0,0,-1);

}



TEST(RTTriangle, shouldHandlePointsOnEitherSideOfTheTriangle) {

  RTTriangle t(Matrix(-2,-2,10), Matrix(2,0,10), Matrix(-2,2,10));
  CHECK_NORMAL_AT(t, Matrix(0,0,10), Matrix(0,0,20), 0,0,1);

}

TEST(RTTriangle, shouldNotIntersectRayGoingTheOtherWay) {

  RTTriangle t(Matrix(-2,-2,10), Matrix(2,0,10), Matrix(-2,2,10));
  CHECK(t.intersect(Ray(Matrix(0,0,0), Matrix(0,0,-1))) == nullptr);

}

TEST(RTTriangle, shouldIntersectTriangle) {
  
  Ray ray(
    Matrix(-9.58771992f, 4.26362991f, 4.60778999f), 
    Matrix(0.74592382f, -0.38657027f, -0.54236609f)
  );

  RTTriangle t(
    Matrix(-6.19481f, -2.18127f, 0.67082f),
    Matrix(3.11895f, -2.18127f, 0.67082f),
    Matrix(3.11895f, -2.18127f, -8.92172f)
  );

  CHECK(t.intersect(ray) != nullptr);

  
}




/* This bug has found a hole to creep into
TEST(RTTriangle, shouldBeAddableToPolySet) {

  RTPolySet *set = new RTPolySet();
  VertexIO vertexIO[] = {
    {{ 0,-5, 10}, {0,0,0}, 0, 0, 0},
    {{ 2, 0, 10}, {0,0,0}, 0, 0, 0},
    {{ 0, 2, 10}, {0,0,0}, 0, 0, 0}
  };

  PolygonIO polygonIO = {
    3, vertexIO
  };

  RTTriangle triangle = RTShapeFactory::createTriangle(&polygonIO);
  triangle.setParent(set);
  set->addTriangle(triangle);

  delete set;
}
*/
