#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GMock.h"
#include "WhittedIlluminator.h"
#include <vector>

TEST_GROUP(WhittedIlluminator) {
	void setup() {}
	void teardown() {}
};

class ShadowTracerMock : public ShadowTracer {
  
public:
  MOCK_METHOD1(getLightSources, std::vector<const Light*>(const Matrix*));
  
};

TEST(WhittedIlluminator, shouldIlluminateWithTheDotProductOfNormalVector) {
 
  RTSphere sphere(Matrix(0,0,0), 1);
  

  NiceMock<ShadowTracerMock> shadowTracerMock;
  std::vector<const Light*> sources;
  Light light(Matrix(0,0,0), Matrix(0,0,0), RTColor(), 0, 0);
  sources.push_back(&light);
  EXPECT_CALL(shadowTracerMock, getLightSources(testing::_)).WillRepeatedly(Return(sources));

  WhittedIlluminator illuminator(&shadowTracerMock);
 
}
