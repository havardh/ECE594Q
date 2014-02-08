#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GMock.h"
#include "WhittedIlluminator.h"
#include "ColorTestHelper.h"
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
    material.setKTransparency(0);
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

void setNormal(Matrix *normal) {
  EXPECT_CALL(*shapeMock, normal(_, _)).WillRepeatedly(Return(MatrixPtr(normal)));
}

TEST(WhittedIlluminator, shouldFullyIlluminateWhenDirectlyInFromOfLightSource) {
  
  setNormal(new Matrix(1,0,0));

  RTColor color = illuminator->illuminate(*intersection);
  COLOR_EQUAL(255, 255, 255, color );
 
}

TEST(WhittedIlluminator, shouldNotIlluminateWhenOnOrthogonalToNormalVector) {
  
	setNormal(new Matrix(0,1,0));

  RTColor color = illuminator->illuminate(*intersection);
  COLOR_EQUAL( 0,0,0, color );
  
}

TEST(WhittedIlluminator, shouldHandleMultipleLightSource) {

  setNormal(new Matrix(0.2,0.2,0.9591663045f));

  Light l2(Matrix(10,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  sources->push_back(&l2);
  EXPECT_CALL(*shadowTracerMock, getLightSources(_)).WillRepeatedly(Return(*sources));

  RTColor color = illuminator->illuminate(*intersection);

  uint8_t xx = (uint8_t)(255*0.2 + 255*0.2);
  COLOR_EQUAL(xx, xx, xx, color);


}

TEST(WhittedIlluminator, shouldCeilToOne) {
  
	setNormal(new Matrix(0.7f, 0.7f, 0.141421355f));

  Light l2(Matrix(10,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  sources->push_back(&l2);
  EXPECT_CALL(*shadowTracerMock, getLightSources(_)).WillRepeatedly(Return(*sources));

  RTColor color = illuminator->illuminate(*intersection);

  COLOR_EQUAL(255,255,255, color);
  
}

TEST(WhittedIlluminator, transpanrancyShouldReduceColorFromDirectLighting) {

  setNormal(new Matrix(1,0,0));
  material.setKTransparency(0.5);
  EXPECT_CALL(*shapeMock, getMaterial(_)).WillRepeatedly(Return(material));

  RTColor color = illuminator->illuminate(*intersection);
  COLOR_EQUAL( 127, 127, 127, color );

}
