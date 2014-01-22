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
