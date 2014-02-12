#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GMock.h"
#include "WhittedIlluminator.h"
#include "ColorTestHelper.h"
#include "RTShapeMock.h"
#include <vector>

using testing::_;

// Mock classes
class ShadowTracerMock : public ShadowTracer {};

// Test Figures
static RTMaterial material; 
static NiceMock<ShadowTracerMock> *shadowTracerMock;
static NiceMock<RTShapeMock> *shapeMock;
static WhittedIlluminator *illuminator;
static Light l1(Matrix(10,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
static Light l2(Matrix(10,0,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
static Scene *scene;

TEST_GROUP(WhittedIlluminator) {
	void setup() {
    material.setDiffColor(RTColor::WHITE);
    material.setSpecColor(RTColor::WHITE);
    material.setShininess(0.2);
    material.setKTransparency(0);

    shadowTracerMock = new NiceMock<ShadowTracerMock>;
    shapeMock = new NiceMock<RTShapeMock>;

    scene = new Scene();
    scene->add(l1);
    ShadowTracer stracer(scene);

    illuminator = new WhittedIlluminator(&stracer, scene);
    illuminator->setShape(shapeMock);
    illuminator->setMaterial(material);
    illuminator->setRayOrigin(Matrix(1,0,0));
    illuminator->setPoint(Matrix(0,0,0));
  }
	void teardown() {
    delete shadowTracerMock;
    delete shapeMock;
    delete scene;
    delete illuminator;
  }
};

void setNormal(Matrix *normal) {
  EXPECT_CALL(*shapeMock, normal(_)).WillRepeatedly(Return(MatrixPtr(normal)));
}

TEST(WhittedIlluminator, shouldFullyIlluminateWhenDirectlyInFrontOfLightSource) {
  
  setNormal(new Matrix(1,0,0));
  
  RTColor color = illuminator->diffuse(&l1);

  COLOR_EQUAL(255, 255, 255, color );
 
}

TEST(WhittedIlluminator, shouldNotIlluminateWhenOnOrthogonalToNormalVector) {
  
	setNormal(new Matrix(0,1,0));

  RTColor color = illuminator->diffuse(&l1);

  COLOR_EQUAL( 0,0,0, color );
  
}

TEST(WhittedIlluminator, shouldHandleMultipleLightSource) {

  setNormal(new Matrix(0.2,0.2,0.9591663045f));
  scene->add(l2);

  RTColor color = illuminator->direct();

  uint8_t xx = (uint8_t)(255*0.2 + 255*0.2);
  COLOR_EQUAL(xx, xx, xx, color);


}

TEST(WhittedIlluminator, shouldCeilToOne) {
  
	setNormal(new Matrix(0.7f, 0.7f, 0.141421355f)); 
  scene->add(l2);

  RTColor color = illuminator->direct();

  COLOR_EQUAL(255,255,255, color);
  
}

TEST(WhittedIlluminator, transpanrancyShouldReduceColorFromDirectLighting) {

  setNormal(new Matrix(1,0,0));
  material.setKTransparency(0.5);
  illuminator->setMaterial(material);
 
  RTColor color = illuminator->diffuse(&l1);
  COLOR_EQUAL( 127, 127, 127, color );

}

TEST(WhittedIlluminator, specularShouldBe1WhenStraightAt) {
  
  setNormal(new Matrix(1,0,0));
  illuminator->setRayOrigin(Matrix(1,0,0));

  RTColor color = illuminator->specular(&l1);

  COLOR_EQUAL(255, 255, 255, color );
  
}

IGNORE_TEST(WhittedIlluminator, specularShouldDecreaseWithNormal) {

  setNormal(new Matrix(1,0,0));
  illuminator->setRayOrigin(Matrix(1,0,0));
  Light l3(Matrix(1,0.000425,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  RTColor color = illuminator->specular(&l3);

  CHECK( color.getRGBRed() > 0 );
  CHECK( color.getRGBRed() < 240 );
  CHECK( color.getRGBGreen() > 0 ); 
  CHECK( color.getRGBGreen() < 240 );
  CHECK( color.getRGBBlue() > 0 ); 
  CHECK( color.getRGBBlue() < 240 );

}

TEST(WhittedIlluminator, specularShouldBeZeroWhenOrthogonal) {

  setNormal(new Matrix(1,0,0));
  illuminator->setRayOrigin(Matrix(1,0,0));
  Light l3(Matrix(0,2,0), Matrix(0,0,0), RTColor::WHITE, 0, 0);
  
  RTColor color = illuminator->specular(&l3);

  COLOR_EQUAL( 0,0,0, color);

}

