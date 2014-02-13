#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/GMock.h"
#include "TimeBenchmark.h"

TEST_GROUP(TimeBenchmark) {
	void setup() {}
	void teardown() {}
};

class ActionMock : public Action {
public:
  MOCK_METHOD0(execute, void());  
  MOCK_METHOD0(describe, const char*());
  MOCK_METHOD0(setup, void());
};

class StopWatchMock : public StopWatch {

};

TEST(TimeBenchmark, runShouldCallAction) {
  
  TimeBenchmark benchmark;
  Timer time; 
  StopWatch stopWatch;
  stopWatch.setTimer(&time);
  benchmark.setStopWatch(&stopWatch);

  NiceMock<ActionMock> action;
  EXPECT_CALL(action, execute());
  benchmark.addAction(&action);

  benchmark.run();

}

TEST(TimeBenchmark, shouldSupportMultipleActions) {

  TimeBenchmark benchmark;
  Timer time; 
  StopWatch stopWatch;
  stopWatch.setTimer(&time);
  benchmark.setStopWatch(&stopWatch);
  

  NiceMock<ActionMock> a1;
  EXPECT_CALL(a1, execute());
  NiceMock<ActionMock> a2;
  EXPECT_CALL(a2, execute());

  benchmark.addAction(&a1);
  benchmark.addAction(&a2);

  benchmark.run();
 
}

TEST(TimeBenchmark, shouldTakeAStopWatch) {

  TimeBenchmark benchmark;
  Timer time; 
  StopWatch stopWatch;
  stopWatch.setTimer(&time);
  benchmark.setStopWatch(&stopWatch);
}

TEST(TimeBenchmark, runShouldCallSetup) {
  
  TimeBenchmark benchmark;
  Timer time; 
  StopWatch stopWatch;
  stopWatch.setTimer(&time);
  benchmark.setStopWatch(&stopWatch);

  NiceMock<ActionMock> action;
  EXPECT_CALL(action, execute());
  EXPECT_CALL(action, setup());
  benchmark.addAction(&action);

  benchmark.run();

}
