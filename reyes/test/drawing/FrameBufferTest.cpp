#include "CppUTest/CommandLineTestRunner.h"
#include "FrameBuffer.h"

TEST_GROUP(FrameBuffer) {
  void setup() {}
  void teardown() {}
};


TEST(FrameBuffer, shouldConstructAndDestruct) {
  
	FrameBuffer s(100, 100);
  
}
