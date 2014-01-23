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
  Color c = { 123, 231, 111 };
  s.set( 99, 99, c );
  Color actual = s.get( 99, 99 ); 

  CHECK_EQUAL( 123, actual.red );
  CHECK_EQUAL( 231, actual.green );
  CHECK_EQUAL( 111, actual.blue );

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
