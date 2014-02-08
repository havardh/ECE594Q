#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GMock.h"
#include "WhittedIlluminator.h"
#include "ColorTestHelper.h"
#include <vector>

using testing::_;

// Mock classes
class ShadowTracerMock : public ShadowTracer {

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
static NiceMock<ShadowTracerMock> *shadowTracerMock;
static NiceMock<RTShapeMock> *shapeMock;
static WhittedIlluminator *illuminator;
static Light l1(Matrix(10,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
static Light l2(Matrix(10,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);

TEST_GROUP(WhittedIlluminator) {
	void setup() {
    material.setDiffColor(RTColor::WHITE);
    material.setKTransparency(0);

    shadowTracerMock = new NiceMock<ShadowTracerMock>;
    shapeMock = new NiceMock<RTShapeMock>;

    illuminator = new WhittedIlluminator(shadowTracerMock);
    illuminator->setShape(shapeMock);
    illuminator->setMaterial(material);
    illuminator->addLightSource(&l1);
    illuminator->setRayOrigin(Matrix(0,0,0));
    illuminator->setPoint(Matrix(0,0,0));
  }
	void teardown() {
    delete shadowTracerMock;
    delete shapeMock;
    delete illuminator;
  }
};

void setNormal(Matrix *normal) {
  EXPECT_CALL(*shapeMock, normal(_, _)).WillRepeatedly(Return(MatrixPtr(normal)));
}

TEST(WhittedIlluminator, shouldFullyIlluminateWhenDirectlyInFrontOfLightSource) {
  
  setNormal(new Matrix(1,0,0));
  
  RTColor color = illuminator->diffuse();

  COLOR_EQUAL(255, 255, 255, color );
 
}

TEST(WhittedIlluminator, shouldNotIlluminateWhenOnOrthogonalToNormalVector) {
  
	setNormal(new Matrix(0,1,0));

  RTColor color = illuminator->diffuse();

  COLOR_EQUAL( 0,0,0, color );
  
}

TEST(WhittedIlluminator, shouldHandleMultipleLightSource) {

  setNormal(new Matrix(0.2,0.2,0.9591663045f));
  illuminator->addLightSource(&l2);

  RTColor color = illuminator->diffuse();

  uint8_t xx = (uint8_t)(255*0.2 + 255*0.2);
  COLOR_EQUAL(xx, xx, xx, color);


}

TEST(WhittedIlluminator, shouldCeilToOne) {
  
	setNormal(new Matrix(0.7f, 0.7f, 0.141421355f)); 
  illuminator->addLightSource(&l2);

  RTColor color = illuminator->diffuse();

  COLOR_EQUAL(255,255,255, color);
  
}

TEST(WhittedIlluminator, transpanrancyShouldReduceColorFromDirectLighting) {

  setNormal(new Matrix(1,0,0));
  material.setKTransparency(0.5);
  illuminator->setMaterial(material);
 
  RTColor color = illuminator->diffuse();
  COLOR_EQUAL( 127, 127, 127, color );

}
