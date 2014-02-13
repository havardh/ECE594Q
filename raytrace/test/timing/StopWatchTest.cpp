#include "CppUTest/CommandLineTestRunner.h"
#include "StopWatch.h"
#include "Timer.h"
#include "CppUTestExt/GMock.h"

class TimerMock : public Timer {
public:
MOCK_METHOD0(time, ull_t());

};

class StopWatchMock : public StopWatch {
public:
  MOCK_METHOD0(run, void());

};

TEST_GROUP(StopWatch) {
  void setup() {}
  void teardown() {}
};

TEST(StopWatch, shouldCallTimerOnStart) {
  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
 
}

TEST(StopWatch, shouldCallTimerOnStop) {
  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.stop();
}

TEST(StopWatch, shouldCallTimerOnLap) {
  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.lap("");
}

TEST(StopWatch, shouldRememberStartTime) {
  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(15));
  benchmark.start("start");
  
  ull_t start = benchmark.getStart();
  CHECK_EQUAL( 15, (int)start );
}

TEST(StopWatch, shouldRememberStopTime) {
  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
  EXPECT_CALL(timerMock, time()).WillOnce(Return(20));
  benchmark.stop();
  
  ull_t stop = benchmark.getStop();
  CHECK_EQUAL( 20, (int)stop );
}

TEST(StopWatch, shouldRememberLapTime) {
  NiceMock<StopWatchMock> benchmark;
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

TEST(StopWatch, shouldReturnZeroByDefault) {

  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  CHECK_EQUAL( 0, (int)benchmark.getStart() );
  CHECK_EQUAL( 0, (int)benchmark.getLap(0) );
  CHECK( 0 == benchmark.getStop() );


}

TEST(StopWatch, lapShouldBeZeroWhenNotTaken) {

  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);

  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");
  EXPECT_CALL(timerMock, time()).WillOnce(Return(5));
  benchmark.stop();

  CHECK_EQUAL( 0, (int)benchmark.getLap(0) );

}

TEST(StopWatch, shouldResetOnStop) {
  NiceMock<StopWatchMock> benchmark;
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

TEST(StopWatch, shouldCountLaps) {
  NiceMock<StopWatchMock> benchmark;
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

TEST(StopWatch, shouldReportTotalTime) {
  
  NiceMock<StopWatchMock> benchmark;
  NiceMock<TimerMock> timerMock;
  benchmark.setTimer(&timerMock);
  
  EXPECT_CALL(timerMock, time()).WillOnce(Return(0));
  benchmark.start("");

  EXPECT_CALL(timerMock, time()).WillOnce(Return(10));
  benchmark.stop();

  CHECK_EQUAL( 10, (int)benchmark.totalDuration() );

}

TEST(StopWatch, shouldReportLapTime) {

  NiceMock<StopWatchMock> benchmark;
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

TEST(StopWatch, shouldReportZeroTimeForNegativeLap) {
  NiceMock<StopWatchMock> benchmark;
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


TEST(StopWatch, shouldReportZeroTimeForToHightLap) {
  NiceMock<StopWatchMock> benchmark;
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



