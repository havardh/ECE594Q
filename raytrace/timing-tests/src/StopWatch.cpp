#include "StopWatch.h"

void StopWatch::setTimer(Timer *timer) {
  _timer = timer;
}

void StopWatch::start(const char*) {
  times.clear(); 
  times.push_back(_timer->time());
}

void StopWatch::lap(const char* name) {
  lapNames.push_back(name);
  times.push_back(_timer->time());
}

void StopWatch::stop() {
  times.push_back(_timer->time());
}

ull_t StopWatch::getStart() {
  if (times.size() < 1) {
    return 0;
  }
  return times.front();
}

ull_t StopWatch::getLap(int i) {
  
  if (times.size() < 3 || i < 0 || i+1 >= times.size()-1) {
    return 0;
  }
  return times[i+1];
}

ull_t StopWatch::getStop() {
  if (times.size() < 2) {
    return 0;
  }
  return times.back();
}

int StopWatch::numLaps() {
  return times.size() - 2;
}

ull_t StopWatch::totalDuration() {
  return getStop() - getStart();
}

ull_t StopWatch::lapTime(int i) {

  if (i == 0) {
    return getLap(i) - getStart();
  }

  return getLap(i) - getLap(i-1);

}

const char* StopWatch::lapName(int i) {
  return lapNames[i];
}

void StopWatch::print() {

  printf("Running Benchmark: <name>\n");
  printf("Start: %llu\n", getStart());
  printf("End: %llu\n", getStop());
  printf("Total Duration: %llu\n", totalDuration());
  printf("Laps recorded: %d\n", numLaps());
  printf("----------------------\n");
  for (int i=0; i<numLaps(); i++) {
    printf("Lap: %s\n", lapName(i));
    printf("Duration %llu\n", lapTime(i));
  }
  printf("----------------------\n");

}
