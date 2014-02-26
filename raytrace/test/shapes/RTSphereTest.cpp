#include "CppUTest/CommandLineTestRunner.h"
#include "MatrixTestHelper.h"
#include "ShapeTestHelper.h"
#include "ColorShaderMock.h"
#include "RTSphere.h"

using testing::_;

TEST_GROUP(RTSphere) {
	void setup() {}
	void teardown() {}
};


#define check_intersects(sphere, origin, direction) \
  { Ray ray(origin, direction);                     \
    CHECK(sphere.intersect(ray) != nullptr); }

#define check_not_intersects(sphere, origin, direction) \
  { Ray ray(origin, direction);                         \
    CHECK(sphere.intersect(ray) == nullptr); }

TEST(RTSphere, shouldCheckForIntersection) {
 
  RTSphere s(Vector(10, 10, 10), 2);

  // A ray straight at it from the origin
  check_intersects(s, Vector(0,0,0), Vector(1,1,1));
  
  // A ray straight at it from x-y axis
  check_intersects(s, Vector(10, 10, 0), Vector(0,0,1));
  // From the axis on the top,bottom,left,right
  check_intersects(s, Vector(8, 10, 0), Vector(0,0,1));
  check_intersects(s, Vector(12, 10, 0), Vector(0,0,1));
  check_intersects(s, Vector(10, 8, 0), Vector(0,0,1));
  check_intersects(s, Vector(10, 12, 0), Vector(0,0,1));
  // From the axis on the corner
  check_not_intersects(s, Vector(8, 12, 0), Vector(0,0,1));
  check_not_intersects(s, Vector(12, 12, 0), Vector(0,0,1));
  check_not_intersects(s, Vector(8, 8, 0), Vector(0,0,1));
  check_not_intersects(s, Vector(12, 8, 0), Vector(0,0,1));

  // Diagonals missing
  check_not_intersects(s, Vector(10, 10, 0), Vector(1,1,1));
}

TEST(RTSphere, shouldIntersectOnClosedPointIfCommingFromTheLeft) {
  
  RTSphere s(Vector(0,0,10), 2);
  
 CHECK_INTERSECTS_AT(s, Ray(Vector(0,0,0), Vector(0,0,1)), 0,0,8);
  
}

TEST(RTSphere, shouldIntersectOnTheSideOfASphere) {

  RTSphere s(Vector(0,0,10), 2);
  
	CHECK_INTERSECTS_AT(s, Ray(Vector(2,0,0), Vector(0,0,1)), 2,0,10);
  
}

TEST(RTSphere, shouldIntersectOnClosedPointIfCommingFromTheRight) {
  
  RTSphere s(Vector(0,0,10), 2);
	CHECK_INTERSECTS_AT(s, Ray(Vector(0,0,20), Vector(0,0,-1)), 0,0,12);
  
}

TEST(RTSphere, normalShouldAlongZAxisNegativeOnFront) {

  RTSphere s(Vector(0,0,10), 1);
  CHECK_NORMAL_AT(s, Vector(0,0,8), 0,0,-1);
  
}

TEST(RTSphere, normalShouldAlongZAxisPositiveOnRear) {

  RTSphere s(Vector(0,0,10), 1);
  CHECK_NORMAL_AT(s, Vector(0,0,12), 0,0,1);
  
}


TEST(RTSphere, normalShouldBeOnXAxisToTheRight) {

  RTSphere s(Vector(0,0,10), 1);
  CHECK_NORMAL_AT(s, Vector(2,0,10), 1,0,0);
  
}

IGNORE_TEST(RTSphere, normalShouldHandlePointInsideSphere) {

  RTSphere s(Vector(0,0,10), 1);
  CHECK_NORMAL_AT(s, Vector(2,0,10), -1,0,0);
  
}



#define TEST_UV_SHADER(point, u, v)                                     \
  NiceMock<ColorShaderMock> shader;                                     \
  ON_CALL(shader, shade(_,_, _)).WillByDefault(Return(RTMaterial()));   \
  RTSphere s(Vector(0,0,10), 1);                                        \
  s.setColorShader(&shader);                                            \
  EXPECT_CALL(shader, shade(u,v, _)).WillRepeatedly(Return(RTMaterial())); \
  s.shadePoint(point);


TEST(RTSphere, shouldCallShaderWithMaterial) {

  RTMaterial m;
  m.setDiffColor(RTColor(0.1,0.9,0.5));
  
  NiceMock<ColorShaderMock> shader;
  ON_CALL(shader, shade(_,_,_)).WillByDefault(Return(RTMaterial()));

  RTSphere s(Vector(0,0,0),1);
  s.addMaterial(m);
  s.setColorShader(&shader);
  s.shadePoint(Vector(0,0,0));

}

TEST(RTSphere, shouldReturnMaterialFromShader) {
  
	RTMaterial m;
  m.setSpecColor(RTColor(0.5,0.3,0.2));

  NiceMock<ColorShaderMock> shader;
  EXPECT_CALL(shader, shade(_,_,_)).WillRepeatedly(Return(m));
  
  RTSphere s(Vector(0,0,0),1);
  s.setColorShader(&shader);
  
  CHECK( s.shadePoint(Vector(0,0,0)) == m );
  
}

IGNORE_TEST(RTSphere, shouldCallShaderWithBottomPoint) {

  TEST_UV_SHADER(Vector(0,-1,10), 0.25, 1);
  
}

IGNORE_TEST(RTSphere, shouldCallShaderWithTopPoint) {

  TEST_UV_SHADER(Vector(0,1,10), 0.25, testing::FloatNear(0, 0.000001));  
}

IGNORE_TEST(RTSphere, shouldCallShaderWithLeft) {

  TEST_UV_SHADER(Vector(-1,0,10), 0.5, 0.5);
}

IGNORE_TEST(RTSphere, shouldCallShaderWithMidFront) {
  TEST_UV_SHADER(Vector(0, 0, 9), 0.25, 0.5);
}

IGNORE_TEST(RTSphere, shouldCallShaderWithMidBack) {
  NiceMock<ColorShaderMock> shader;
  ON_CALL(shader, shade(_,_, _)).WillByDefault(Return(RTMaterial()));
  RTSphere s(Vector(0,0,10), 1);
  s.setColorShader(&shader);

  EXPECT_CALL(shader, shade(0.75, 0.5, _)).WillOnce(Return(RTMaterial()));
  s.shadePoint(Vector(0, 0, 11));
}

TEST(RTSphere, shouldReportOriginAsPosition) {

  RTSphere s(Vector(1,2,3), 1);

  DOUBLES_EQUAL(1, s.getPosition().x(), 0.0001);
  DOUBLES_EQUAL(2, s.getPosition().y(), 0.0001);
  DOUBLES_EQUAL(3, s.getPosition().z(), 0.0001);

}

TEST(RTSphere, shouldReturnBoundingBox) {

  RTSphere s(Vector(1, 0, 10), 2);

  BoundingBox box = s.getBoundingBox();

  VECTOR_EQUAL( -1, -2, 8, box.getOrigin() );
  VECTOR_EQUAL( 4,4,4, box.getDelta() );

}

TEST(RTSphere, shouldIntersectOnInsideOfSphere) {

  RTSphere s(Vector(0, 0, 0), 2);

  Ray ray(Vector(0,0,0), Vector(0,0,1));

  IntersectionPtr I = s.intersect(ray);
  CHECK( I != nullptr );
  Vector P = I->getPoint();

  VECTOR_EQUAL( 0,0,2, P);

}
