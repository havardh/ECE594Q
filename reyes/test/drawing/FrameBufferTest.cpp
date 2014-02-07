#include "CppUTest/CommandLineTestRunner.h"
#include "FrameBuffer.h"

TEST_GROUP(FrameBuffer) {
  void setup() {}
  void teardown() {}
};


TEST(FrameBuffer, shouldConstructAndDestruct) {
  
	FrameBuffer s(1, 1);
  
}

IGNORE_TEST(FrameBuffer, shouldSetAndGet) {

  FrameBuffer fb(100, 100);
  Color c = { 1, 231, 111 };
  fb.set( 99, 99, c );
  Color actual = fb.get( 99, 99 ); 

  CHECK_EQUAL( 1, actual.red );
  CHECK_EQUAL( 231, actual.green );
  CHECK_EQUAL( 111, actual.blue );

}

TEST(FrameBuffer, shouldRetainColorOnlyIfZIsHigher) {
  
	FrameBuffer fb(1,1);
  float z0 = 1.0;
  Color c0 = { 1, 1, 1 };
  for (int i=0; i<16; i++) 
    fb.set(0, 0, i, c0, z0);

  float z1 = 0.5;
  Color c1 = { 2, 2, 2 };
  for (int i=0; i<16; i++) 
    fb.set(0, 0, i, c1, z1);
  
  Color a0 = fb.get(0,0);
  CHECK_EQUAL( 2, a0.red );
  CHECK_EQUAL( 2, a0.green );
  CHECK_EQUAL( 2, a0.blue );

  float z2 = 0.7f;
  Color c2 = { 3,3,3 };
  for (int i=0; i<16; i++) 
    fb.set(0, 0, i, c2, z2);

  Color a1 = fb.get(0,0);
  CHECK_EQUAL( 2, a1.red );
  CHECK_EQUAL( 2, a1.green );
  CHECK_EQUAL( 2, a1.blue );
}

TEST(FrameBuffer, shouldSupportOpacity) {
  
  FrameBuffer fb(1,1);
  float z0 = 1.0;
  Color c0 = { 0, 0, 0 };
  for (int i=0; i<16; i++) 
    fb.set(0, 0, i, c0, z0, 1);

  float z1 = 0.5;
  Color c1 = { 10, 10, 10 };
  for (int i=0; i<16; i++) 
    fb.set(0, 0, i, c1, z1, 0.5);
  
  Color a0 = fb.get(0,0);
  CHECK_EQUAL( 5, a0.red );
  CHECK_EQUAL( 5, a0.green );
  CHECK_EQUAL( 5, a0.blue );
  
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

class PolyMock : public MyPolygon {

  

};

IGNORE_TEST(FrameBuffer, shouldSampleAMicroMyPolygon) {

  FrameBuffer fb(10, 10);
  PolyMock p;
  Color c = { 1,1,1 };
  p.setColor(c);
  p.set(0, new Matrix(1, 1, 0, 1));
  p.set(1, new Matrix(1, -1, 0, 1));
  p.set(2, new Matrix(-1, -1, 0, 1));
  p.set(3, new Matrix(-1, 1, 0, 1));
  fb.draw(p);

  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      Color actual = fb.get(i,j);

      CHECK_EQUAL(1, actual.red);
      CHECK_EQUAL(1, actual.green);
      CHECK_EQUAL(1, actual.blue);
    }
  }

  free(p.get(0));
  free(p.get(1));
  free(p.get(2));
  free(p.get(3));

}
