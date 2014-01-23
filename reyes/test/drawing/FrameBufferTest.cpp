#include "CppUTest/CommandLineTestRunner.h"
#include "FrameBuffer.h"

TEST_GROUP(FrameBuffer) {
  void setup() {}
  void teardown() {}
};


TEST(FrameBuffer, shouldConstructAndDestruct) {
  
	FrameBuffer s(100, 100);
  
}

TEST(FrameBuffer, shouldSetAndGet) {

  FrameBuffer s(100, 100);
  Color c = { 1, 231, 111 };
  s.set( 99, 99, c );
  Color actual = s.get( 99, 99 ); 

  CHECK_EQUAL( 1, actual.red );
  CHECK_EQUAL( 231, actual.green );
  CHECK_EQUAL( 111, actual.blue );

}

TEST(FrameBuffer, shouldSetSampleAndGetAverage) {

  Color white = { 255, 255, 255 };
  Color black = { 0, 0, 0 };
  Color grey = { 255 / 2, 255 / 2, 255 / 2 };

  FrameBuffer fb(1,1);
  for (int i=0; i<8; i++) 
    fb.set(0,0, i, white);

  for (int i=8; i<16; i++)
    fb.set(0,0, i, black);

  Color actual = fb.get(0,0);
  CHECK_EQUAL( grey.red, actual.red);
  CHECK_EQUAL( grey.green, actual.red);
  CHECK_EQUAL( grey.blue, actual.red);

}

class PolyMock : public Micropolygon {

  

};

TEST(FrameBuffer, shouldSampleAMicroPolygon) {

  FrameBuffer fb(10, 10);
  PolyMock p;
  Color c = { 1,1,1 };
  p.setColor(c);
  p.set(0, Matrix(1, 1, 0, 1));
  p.set(1, Matrix(1, -1, 0, 1));
  p.set(2, Matrix(-1, -1, 0, 1));
  p.set(3, Matrix(-1, 1, 0, 1));
  fb.drawMicropolygon(p);

  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      Color actual = fb.get(i,j);

      CHECK_EQUAL(1, actual.red);
      CHECK_EQUAL(1, actual.green);
      CHECK_EQUAL(1, actual.blue);
    }
  }
}
