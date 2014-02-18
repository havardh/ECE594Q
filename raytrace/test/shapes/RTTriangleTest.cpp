#include "CppUTest/CommandLineTestRunner.h"
#include "ShapeTestHelper.h"
#include "ColorTestHelper.h"
#include "MatrixTestHelper.h"
#include "RTTriangle.h"
#include "RTShapeFactory.h"
#include "ColorShaderMock.h"
#include "Vector.h"
#include <vector>

using testing::_;

TEST_GROUP(RTTriangle) {
	void setup() {}
	void teardown() {}
};

TEST(RTTriangle, shouldCheckForIntersection) {
  
  RTTriangle triangle(Vector(1,1,20), Vector(2,1,40), Vector(2,2,10));

  CHECK(triangle.intersect(Ray(Vector(1,1,0), Vector(0,0,1))) != nullptr);
  CHECK(triangle.intersect(Ray(Vector(0,1,0), Vector(0,0,1))) == nullptr);

}

TEST(RTTriangle, shouldReturnIntersectionPoint) {

  RTTriangle t(Vector(-2,-2,10), Vector(2,0,10), Vector(-2,2,10));
  CHECK_INTERSECTS_AT(t, Ray(Vector(0,0,0), Vector(0,0,1)), 0,0,10);

}

TEST(RTTriangle, shouldReturnIntersectionPointOnARotatedTriangle) {

  RTTriangle t(Vector(-2,-2,20), Vector(2,0,20), Vector(-2,2,10));
  CHECK_INTERSECTS_AT(t, Ray(Vector(0,0,0), Vector(0,0,1)), 0,0,17.5f);

}

TEST(RTTriangle, shouldReturnSurfaceNormalInDirectionOfTheRay) {

  RTTriangle t(Vector(-2,-2,10), Vector(2,0,10), Vector(-2,2,10));
  CHECK_NORMAL_AT(t, Vector(0,0,10), 0,0,-1);

}

TEST(RTTriangle, shouldInterpolateCorners) {

  RTTriangle t1(
    Vector(0,0,0), Vector(-1, 0, 2), Vector(1, 0, 2),
    Vector(0,1,0), Vector(0, 1, 0), Vector(0, 0.5, 0)
  );

  CHECK_NORMAL_AT(t1, Vector(0, 0, 2), 0, 1, 0);

  RTTriangle t2(
    Vector(0,0,0), Vector(10, 0, 0), Vector(0, 10, 0),
    Vector(0,0,1), Vector(0, 1, 0), Vector(1, 0, 0)
  );
  CHECK_NORMAL_AT(t2, Vector(5,5,0), 0.707107, 0.707107, 0);
  
}



IGNORE_TEST(RTTriangle, shouldHandlePointsOnEitherSideOfTheTriangle) {

  RTTriangle t(Vector(-2,-2,10), Vector(2,0,10), Vector(-2,2,10));
  CHECK_NORMAL_AT(t, Vector(0,0,10), 0,0,1);

}

TEST(RTTriangle, shouldNotIntersectRayGoingTheOtherWay) {

  RTTriangle t(Vector(-2,-2,10), Vector(2,0,10), Vector(-2,2,10));
  CHECK(t.intersect(Ray(Vector(0,0,0), Vector(0,0,-1))) == nullptr);

}

TEST(RTTriangle, shouldIntersectTriangle) {
  
  Ray ray(
    Vector(-9.58771992f, 4.26362991f, 4.60778999f), 
    Vector(0.74592382f, -0.38657027f, -0.54236609f)
  );

  RTTriangle t(
    Vector(-6.19481f, -2.18127f, 0.67082f),
    Vector(3.11895f, -2.18127f, 0.67082f),
    Vector(3.11895f, -2.18127f, -8.92172f)
  );

  CHECK(t.intersect(ray) != nullptr);

  
}

#define CHECK_UV_TRIANGLE(t, point, u,v, isUpper)                       \
  NiceMock<ColorShaderMock> shader;                                     \
  ON_CALL(shader, shade(_,_, _)).WillByDefault(Return(RTMaterial()));   \
  t.setIsUpper(isUpper);                                                \
  t.setColorShader(&shader);                                            \
  EXPECT_CALL(shader, shade( testing::FloatNear(u, 0.00001), testing::FloatNear(v, 0.00001), _)).WillRepeatedly(Return(RTMaterial())); \
  t.shadePoint(point);


TEST(RTTriangle, shouldInterpolateAtTopInUpper) {

  RTTriangle t(Vector(1,1,0), Vector(1,0,0), Vector(0,1,0));
  CHECK_UV_TRIANGLE(t, Vector(1,1,0), 0,0, true);
}

TEST(RTTriangle, shouldInterpolateAtBottomInLower) {

  RTTriangle t(Vector(0,0,0), Vector(1,0,0), Vector(0,1,0));
  CHECK_UV_TRIANGLE(t, Vector(0,0,0), 1,1, false);
}

TEST(RTTriangle, shouldInterpolateAtCenter) {

  RTTriangle t(Vector(0,0,0), Vector(1,0,0), Vector(0,1,0));
  CHECK_UV_TRIANGLE(t, Vector(0.5,0.5,0), 0.5,0.5, false);
}

TEST(RTTriangle, shouldInterpolateMaterial) {

  RTTriangle t(Vector(0,0,0), Vector(1,0,0), Vector(0,1,0));
  t.setHasMaterial(true);
  RTMaterial m0; m0.setKTransparency(0.1);
  RTMaterial m1; m1.setKTransparency(0.3);
  RTMaterial m2; m2.setKTransparency(0.2);
  t.setM0(&m0);
  t.setM1(&m1);
  t.setM2(&m2);
 
  RTMaterial m = t.interpolateMaterial(Vector(0,0,0));

  DOUBLES_EQUAL( 0.1, m.getKTransparency(), 0.000001 );

}


TEST(RTTriangle, shouldInterpolateMaterialCorrectly) {

  RTTriangle t(
    Vector(0.11763100, -3.31603003, 1.86602998), 
    Vector(0.11763100, -2.81603003, 2.00000000), 
    Vector(-0.64773601, -2.81602001, 1.84775996)
  );
  t.setHasMaterial(true);
  RTMaterial m0; m0.setDiffColor(RTColor(0.721809, 0.670898, 0.670898));
  RTMaterial m1; m1.setDiffColor(RTColor(0.371834, 0.220930, 0.220930));
  RTMaterial m2; m2.setDiffColor(RTColor(0.721010, 0.669870, 0.669870));
  t.setM0(&m0);
  t.setM1(&m1);
  t.setM2(&m2);
 
  RTMaterial m = t.interpolateMaterial(
    Vector(0.09652395, -3.29542994, 1.86735082)
  );

  

  COLOR_EQUAL( 182, 169, 169, m.getDiffColor() );
  

}

TEST(RTTriangle, shouldReportP0asPosition) {

  RTTriangle triangle(Vector(0,1,0), Vector(1,0,1), Vector(1,0,1));

  DOUBLES_EQUAL(0, triangle.getPosition().x(), 0.0001);
  DOUBLES_EQUAL(1, triangle.getPosition().y(), 0.0001);
  DOUBLES_EQUAL(0, triangle.getPosition().z(), 0.0001);


}

TEST(RTTriangle, shouldReturnBoundingBox) {

  RTTriangle triangle(Vector(0,0.1,1), Vector(1,0,0.5), Vector(0.3,1,0));
  
  BoundingBox box = triangle.getBoundingBox();

  VECTOR_EQUAL(0,0,0, box.getOrigin());
  VECTOR_EQUAL(1,1,1, box.getDelta());

}
