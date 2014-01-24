#include "CppUTest/CommandLineTestRunner.h"
#include "ZBuffer.h"

TEST_GROUP(ZBuffer) {
  void setup() {}
  void teardown() {}
};

TEST(ZBuffer, shoudlBeConstructed) {
  
	ZBuffer buffer;
  (void) buffer;
  
}

TEST(ZBuffer, shouldSuppertAddAndGetASample) {
  
  ZBuffer buffer;
  
	Sample sample = {
    1, 1, { 1,1,1 }
  };

  buffer.add(sample);

  Sample actual = buffer.get();
  DOUBLES_EQUAL( 1, actual.z, 0.0001);
  
}

TEST(ZBuffer, shouldSortOnZ) {

  ZBuffer buffer;
  
  Sample samples[] = {
    { 0.2f, 0.1f, { 2,2,2 } },
    { 0.1f, 0.1f, { 1,1,1 } },
    { 0.3f, 0.1f, { 3,3,3 } }
  };

  buffer.add(samples[0]);
  buffer.add(samples[1]);
  buffer.add(samples[2]);

  Sample actuals[] = {
    buffer.get(), buffer.get(), buffer.get()
  };

  DOUBLES_EQUAL( 1, actuals[0].color.red, 0.0001);
  DOUBLES_EQUAL( 2, actuals[1].color.red, 0.0001);
  DOUBLES_EQUAL( 3, actuals[2].color.red, 0.0001);
}

TEST(ZBuffer, shouldStopReturningWhenOpacityIsOne) {

  ZBuffer buffer;
  
  Sample samples[] = {
    { 0.2f, 1, { 2,2,2 } },
    { 0.1f, 0.1f, { 1,1,1 } },
    { 0.3f, 0.1f, { 3,3,3 } }
  };

  buffer.add(samples[0]);
  buffer.add(samples[1]);
  buffer.add(samples[2]);

  Sample actuals[] = {
    buffer.get(), buffer.get(), buffer.get()
  };

  DOUBLES_EQUAL( 1, actuals[0].color.red, 0.0001);
  DOUBLES_EQUAL( 2, actuals[1].color.red, 0.0001);
  DOUBLES_EQUAL( -1, actuals[2].z, 0.0001);

}

TEST(ZBuffer, shouldProvideGetColorFunctionWhichBlendsOpacities) {
  
  ZBuffer buffer;

	Sample samples[] = {
    { 0.1f, 0.5, { 10, 10, 10 } },
    { 0.1f, 1.0, { 20, 20, 20 } },
  };

  buffer.add(samples[0]);
  buffer.add(samples[1]);

  Color c = buffer.getColor();

  CHECK_EQUAL( 15, c.red );
  CHECK_EQUAL( 15, c.green );
  CHECK_EQUAL( 15, c.blue );
  
}
