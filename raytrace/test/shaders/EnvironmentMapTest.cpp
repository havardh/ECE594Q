#include "CppUTest/CommandLineTestRunner.h"
#include "EnvironmentMap.h"

#define ENV_CHECK_UV( vec, eu, ev)                \
  { EnvironmentMap map;                            \
  float u,v;                                      \
                                                  \
  Vector vector = vec;                            \
  Ray ray(Vector(0,0,0), vector.normalize());     \
  map.setUV(ray, u,v);                            \
                                                  \
  DOUBLES_EQUAL(eu, u, 0.0001);                   \
  DOUBLES_EQUAL(ev, v, 0.0001); }


TEST_GROUP(EnvironmentMapPositiveZSection) {};

TEST(EnvironmentMapPositiveZSection, shouldBeInMiddleTopSection) {
  
  ENV_CHECK_UV(Vector(0,0,1), 0.375, 0.5);         // Center
  ENV_CHECK_UV(Vector(1,1,1), (1/4.0), (2/3.0));   // Right Top
  ENV_CHECK_UV(Vector(-1,-1,1), (1/2.0), (1/3.0)); // Left Bottom
  ENV_CHECK_UV(Vector(1,-1,1), (1/2.0), (2/3.0));  // Right Bottom
  ENV_CHECK_UV(Vector(-1,1,1), (1/4.0), (1/3.0));  // Left Top
  ENV_CHECK_UV(Vector(0,1,1), (1/4.0), (1/2.0));   // Top Center
}

TEST_GROUP(EnvironmentMapNegativeZSection) {};
TEST(EnvironmentMapPositiveZSection, shouldBeInMiddleBottomSection) {

  ENV_CHECK_UV(Vector(0,0,-1), (7/8.0), 0.5);       // Center
  ENV_CHECK_UV(Vector(1,1,-1), (8/8.0), (1/3.0));   // Right Top
  ENV_CHECK_UV(Vector(-1,-1,-1), (6/8.0), (2/3.0)); // Left Botton

}

TEST_GROUP(EnvironmentMapPositiveXSection) {};
TEST(EnvironmentMapPositiveXSection, shouldBeInMiddleRightSection) {

  ENV_CHECK_UV(Vector(1,0,0), (3/8.0), (5/6.0));            // Center
  ENV_CHECK_UV(Vector(1,0.9999,-0.9999), (2/8.0), (2/3.0)); // Left Top
  ENV_CHECK_UV(Vector(1,-0.9999,0.9999), (4/8.0), (3/3.0)); // Right Botton
}

TEST_GROUP(EnvironmentMapNegativeXSection) {};
TEST(EnvironmentMapNegativeXSection, shouldBeInMiddleLeftSection) {

  ENV_CHECK_UV(Vector(-1,0,0), (3/8.0), (1/6.0));              // Center
  ENV_CHECK_UV(Vector(-1, 0.9999, 0.9999), (2/8.0), 0);        // Left Top
  ENV_CHECK_UV(Vector(-1, -0.9999,-0.9999), (4/8.0), (1/3.0)); // Right Botton
}

TEST_GROUP(EnvironmentMapPositiveYSection) {};
TEST(EnvironmentMapPositiveYSection, shouldBeInTopSection) {

  ENV_CHECK_UV(Vector(0,1,0), (1/8.0), (3/6.0));              // Center
  ENV_CHECK_UV(Vector(-0.9999, 1, 0.9999), 0, (1/3.0));        // Left Top
  ENV_CHECK_UV(Vector(0.9999, 1, -0.9999), (2/8.0), (2/3.0)); // Right Botton
}

TEST_GROUP(EnvironmentMapNegativeYSection) {};
TEST(EnvironmentMapNegativeYSection, shouldBeInBottomMiddleSection) {

  ENV_CHECK_UV(Vector(0,-1,0), (5/8.0), (3/6.0));              // Center
  ENV_CHECK_UV(Vector(-0.9999, -1, -0.9999), (4/8.0), (1/3.0));        // Left Top
  ENV_CHECK_UV(Vector(0.9999, -1, 0.9999), (6/8.0), (2/3.0)); // Right Botton
}

TEST_GROUP(EnvironmentMap) {};
TEST(EnvironmentMap, shouldHandlePointsOverMean) {
  
  EnvironmentMap map;
  float u,v;

  Vector vector(0.549277, 0.592175, -0.589597);
  Ray ray(Vector(0,0,0), vector.normalize());
  map.setUV(ray, u,v);

  CHECK ( u >= 0 && u <= 1 );
  CHECK ( v >= 0 && v <= 1 );
  
}
