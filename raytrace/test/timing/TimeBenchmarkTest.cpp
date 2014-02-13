#include "CppUTest/CommandLineTestRunner.h"
#include "TimeBenchmark.h"
#include "Timer.h"
#include "CppUTestExt/GMock.h"

class TimerMock : public Timer {
public:
MOCK_METHOD0(time, ull_t());

};

class TimeBenchmarkMock : public TimeBenchmark {
public:
  MOCK_METHOD0(run, void());

};


TEST_GROUP(TimeBenchmark) {
  void setup() {}
  void teardown() {}
};

TEST(TimeBenchmark, shouldCallTimerOnStart) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
 
}

TEST(TimeBenchmark, shouldCallTimerOnStop) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.stop();
}

TEST(TimeBenchmark, shouldCallTimerOnLap) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.lap("");
}

TEST(TimeBenchmark, shouldRememberStartTime) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(15));
  benchmark.start("start");
  
  ull_t start = benchmark.getStart();
  CHECK_EQUAL( 15, (int)start );
}

TEST(TimeBenchmark, shouldRememberStopTime) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
  EXPECT_CALL(timerMock, time()).WillOnce(Return(20));
  benchmark.stop();
  
  ull_t stop = benchmark.getStop();
  CHECK_EQUAL( 20, (int)stop );
}

TEST(TimeBenchmark, shouldRememberLapTime) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.lap("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(15));
  benchmark.lap("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(20));
  benchmark.stop();
  
  CHECK_EQUAL( 10, (int)benchmark.getLap(0) );
  CHECK_EQUAL( 15, (int)benchmark.getLap(1) );
  
}

TEST(TimeBenchmark, shouldReturnZeroByDefault) {

  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  CHECK_EQUAL( 0, (int)benchmark.getStart() );
  CHECK_EQUAL( 0, (int)benchmark.getLap(0) );
  CHECK( 0 == benchmark.getStop() );


}

TEST(TimeBenchmark, lapShouldBeZeroWhenNotTaken) {

  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.stop();

  CHECK_EQUAL( 0, (int)benchmark.getLap(0) );

}

TEST(TimeBenchmark, shouldResetOnStop) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.stop();
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.start("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(15));
  benchmark.stop();

  CHECK_EQUAL( 10, (int)benchmark.getStart() );
  CHECK_EQUAL( 0, (int)benchmark.getLap(0) );
  CHECK_EQUAL( 15, (int)benchmark.getStop() );
}

TEST(TimeBenchmark, shouldCountLaps) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.stop();

  CHECK_EQUAL( 3, benchmark.numLaps() );
  
}

TEST(TimeBenchmark, shouldReportTotalTime) {
  
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.stop();

  CHECK_EQUAL( 10, (int)benchmark.totalDuration() );

}

TEST(TimeBenchmark, shouldReportLapTime) {

  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  EXPECT_CALL(timerMock, time()).WillOnce(Return(2));
  benchmark.start("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.stop();

  CHECK_EQUAL( 3, (int)benchmark.lapTime(0) );
  CHECK_EQUAL( 0, (int)benchmark.lapTime(1) );
  
}

TEST(TimeBenchmark, shouldReportZeroTimeForNegativeLap) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.stop();

  CHECK_EQUAL( 0, (int)benchmark.getLap(-5));
  CHECK_EQUAL( 1, benchmark.numLaps() );
}


TEST(TimeBenchmark, shouldReportZeroTimeForToHightLap) {
  NiceMock<TimeBenchmarkMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.lap("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.stop();

  CHECK_EQUAL( 0, (int)benchmark.getLap(1));
}



