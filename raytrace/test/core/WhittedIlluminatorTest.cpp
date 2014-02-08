#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GMock.h"
#include "WhittedIlluminator.h"
#include <vector>

using testing::_;

// Mock classes
class ShadowTracerMock : public ShadowTracer {
public:
  MOCK_METHOD1(getLightSources, std::vector<const Light*>(const Matrix*));
};

class RTShapeMock : public RTShape {
public:
  MOCK_CONST_METHOD0(getMaterialCount, int());
  MOCK_CONST_METHOD1(getMaterial, const RTMaterial(int));
  MOCK_METHOD1(intersect, IntersectionPtr(const Ray));
  MOCK_METHOD2(normal, MatrixPtr(const Matrix&, const Matrix&));
  MOCK_METHOD0(print, void());
};

// Test Figures
static RTMaterial material; 
static std::vector<const Light*>* sources;
static NiceMock<ShadowTracerMock> *shadowTracerMock;
static NiceMock<RTShapeMock> *shapeMock;
static WhittedIlluminator *illuminator;
static Intersection *intersection;
static Light *light;

TEST_GROUP(WhittedIlluminator) {
	void setup() {
    material.setDiffColor(RTColor::WHITE);
    light = new Light(Matrix(10,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
    sources = new std::vector<const Light*>;
    sources->push_back(light);

    shadowTracerMock = new NiceMock<ShadowTracerMock>;
    EXPECT_CALL(*shadowTracerMock, getLightSources(_)).WillRepeatedly(Return(*sources));

    shapeMock = new NiceMock<RTShapeMock>;
    EXPECT_CALL(*shapeMock, getMaterial(_)).WillRepeatedly(Return(material));
    EXPECT_CALL(*shapeMock, getMaterialCount()).WillRepeatedly(Return(1));

    illuminator = new WhittedIlluminator(shadowTracerMock);
    intersection = new Intersection(shapeMock, Ray(Matrix(0,0,0), Matrix(0,0,0)), Matrix(0,0,0));
  }
	void teardown() {
    delete light;
    delete sources;
    delete shadowTracerMock;
    delete shapeMock;
    delete illuminator;
    delete intersection;
  }
};

TEST(WhittedIlluminator, shouldFullyIlluminateWhenDirectlyInFromOfLightSource) {
  
  EXPECT_CALL(*shapeMock, normal(_, _)).WillRepeatedly(Return(MatrixPtr(new Matrix(1,0,0))));

  RTColor color = illuminator->illuminate(*intersection);
  CHECK_EQUAL(255, color.getRGBRed());
  CHECK_EQUAL(255, color.getRGBGreen());
  CHECK_EQUAL(255, color.getRGBBlue());
 
}

TEST(WhittedIlluminator, shouldNotIlluminateWhenOnOrthogonalToNormalVector) {
  
	EXPECT_CALL(*shapeMock, normal(_, _)).WillRepeatedly(Return(MatrixPtr(new Matrix(0,1,0))));

  RTColor color = illuminator->illuminate(*intersection);
  CHECK_EQUAL(0, color.getRGBRed());
  CHECK_EQUAL(0, color.getRGBGreen());
  CHECK_EQUAL(0, color.getRGBBlue());
  
}

