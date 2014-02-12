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
 
  RTSphere s(Matrix(10, 10, 10), 2);

  // A ray straight at it from the origin
  check_intersects(s, Matrix(0,0,0), Matrix(1,1,1));
  
  // A ray straight at it from x-y axis
  check_intersects(s, Matrix(10, 10, 0), Matrix(0,0,1));
  // From the axis on the top,bottom,left,right
  check_intersects(s, Matrix(8, 10, 0), Matrix(0,0,1));
  check_intersects(s, Matrix(12, 10, 0), Matrix(0,0,1));
  check_intersects(s, Matrix(10, 8, 0), Matrix(0,0,1));
  check_intersects(s, Matrix(10, 12, 0), Matrix(0,0,1));
  // From the axis on the corner
  check_not_intersects(s, Matrix(8, 12, 0), Matrix(0,0,1));
  check_not_intersects(s, Matrix(12, 12, 0), Matrix(0,0,1));
  check_not_intersects(s, Matrix(8, 8, 0), Matrix(0,0,1));
  check_not_intersects(s, Matrix(12, 8, 0), Matrix(0,0,1));

  // Diagonals missing
  check_not_intersects(s, Matrix(10, 10, 0), Matrix(1,1,1));
}

TEST(RTSphere, shouldIntersectOnClosedPointIfCommingFromTheLeft) {
  
  RTSphere s(Matrix(0,0,10), 2);
  
  CHECK_INTERSECTS_AT(s, Ray(Matrix(0,0,0), Matrix(0,0,1)), 0,0,8);
  
}

TEST(RTSphere, shouldIntersectOnTheSideOfASphere) {

  RTSphere s(Matrix(0,0,10), 2);
  
	CHECK_INTERSECTS_AT(s, Ray(Matrix(2,0,0), Matrix(0,0,1)), 2,0,10);
  
}

TEST(RTSphere, shouldIntersectOnClosedPointIfCommingFromTheRight) {
  
  RTSphere s(Matrix(0,0,10), 2);
	CHECK_INTERSECTS_AT(s, Ray(Matrix(0,0,20), Matrix(0,0,-1)), 0,0,12);
  
}

TEST(RTSphere, normalShouldAlongZAxisNegativeOnFront) {

  RTSphere s(Matrix(0,0,10), 1);
  CHECK_NORMAL_AT(s, Matrix(0,0,8), 0,0,-1);
  
}

TEST(RTSphere, normalShouldAlongZAxisPositiveOnRear) {

  RTSphere s(Matrix(0,0,10), 1);
  CHECK_NORMAL_AT(s, Matrix(0,0,12), 0,0,1);
  
}


TEST(RTSphere, normalShouldBeOnXAxisToTheRight) {

  RTSphere s(Matrix(0,0,10), 1);
  CHECK_NORMAL_AT(s, Matrix(2,0,10), 1,0,0);
  
}

IGNORE_TEST(RTSphere, normalShouldHandlePointInsideSphere) {

  RTSphere s(Matrix(0,0,10), 1);
  CHECK_NORMAL_AT(s, Matrix(2,0,10), -1,0,0);
  
}



#define TEST_UV_SHADER(point, u, v)                                     \
  NiceMock<ColorShaderMock> shader;                                     \
  ON_CALL(shader, shade(_,_, _)).WillByDefault(Return(RTMaterial()));   \
  RTSphere s(Matrix(0,0,10), 1);                                        \
  s.setColorShader(&shader);                                            \
  EXPECT_CALL(shader, shade(u,v, _)).WillRepeatedly(Return(RTMaterial())); \
  s.shadePoint(point);


TEST(RTSphere, shouldCallShaderWithMaterial) {

  

}

TEST(RTSphere, shouldCallShaderWithBottomPoint) {

  TEST_UV_SHADER(Matrix(0,-1,10), 0.25, 1);
  
}

TEST(RTSphere, shouldCallShaderWithTopPoint) {

  TEST_UV_SHADER(Matrix(0,1,10), 0.25, testing::FloatNear(0, 0.000001));  
}


TEST(RTSphere, shouldCallShaderWithLeft) {

  TEST_UV_SHADER(Matrix(-1,0,10), 0.5, 0.5);
}


TEST(RTSphere, shouldCallShaderWithMidFront) {
  TEST_UV_SHADER(Matrix(0, 0, 9), 0.25, 0.5);
}


IGNORE_TEST(RTSphere, shouldCallShaderWithMidBack) {
  NiceMock<ColorShaderMock> shader;
  ON_CALL(shader, shade(_,_, _)).WillByDefault(Return(RTMaterial()));
  RTSphere s(Matrix(0,0,10), 1);
  s.setColorShader(&shader);

  EXPECT_CALL(shader, shade(0.75, 0.5, _)).WillOnce(Return(RTMaterial()));
  s.shadePoint(Matrix(0, 0, 11));
}
