#include "TimeBenchmark.h"

void TimeBenchmark::setTimer(Timer *timer) {
  _timer = timer;
}

void TimeBenchmark::start(const char*) {
  times.clear(); 
  times.push_back(_timer->time());
}

void TimeBenchmark::lap(const char*) {
  times.push_back(_timer->time());
}

void TimeBenchmark::stop() {
  times.push_back(_timer->time());
}

ull_t TimeBenchmark::getStart() {
  if (times.size() < 1) {
    return 0;
  }
  return times.front();
}

ull_t TimeBenchmark::getLap(int i) {
  
  if (times.size() < 3 || i < 0 || i+1 >= times.size()-1) {
    return 0;
  }
  return times[i+1];
}

ull_t TimeBenchmark::getStop() {
  if (times.size() < 2) {
    return 0;
  }
  return times.back();
}

int TimeBenchmark::numLaps() {
  return times.size() - 2;
}

ull_t TimeBenchmark::totalDuration() {
  return getStop() - getStart();
}

ull_t TimeBenchmark::lapTime(int i) {

  if (i == 0) {
    return getLap(i) - getStart();
  }

  return getLap(i) - getLap(i-1);

}

void TimeBenchmark::print() {

  printf("Running Benchmark: <name>\n");
  printf("Start: %llu\n", getStart());
  printf("End: %llu\n", getStop());
  printf("Total Duration: %llu\n", totalDuration());
  printf("Laps recorded: %d\n", numLaps());
  printf("----------------------\n");
  for (int i=0; i<numLaps(); i++) {
    printf("Lap: <lap name>\n");
    printf("Duration %llu\n", lapTime(i));
  }
  printf("----------------------\n");

}
